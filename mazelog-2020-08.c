#include <stdio.h>

enum {G=0x10, B=0x20, R=0x30, V=0x40};
enum {D=0x01, S=0x02, C=0x03, P=0x04, X=0x05};

#define H 5
#define W 5
static const signed char grid[] = {
    G|D, G|C, G|C, B|C, B|D,
    B|S,   0, B|C,   0, R|S,
    B|D, R|D, R|C, R|X, R|C,
    V|D,   0, V|C,   0, B|D,
    B|X, B|X, V|C, B|C, R|P,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n - 1] == W * H - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n - 1] % W;
        int y = p[n - 1] / W;
        int m = n % 2 ? 0x0f : 0xf0;
        for (int i = 0; i < 4; i++) {
            if (x % 2 == 1 && i > 1) continue;
            if (y % 2 == 1 && i < 2) continue;
            for (int v = 1; ; v++) {
                int tx = x + v * moves[i * 2 + 0];
                int ty = y + v * moves[i * 2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int t = ty * W + tx;
                    if ((grid[t] & m) == (grid[p[n-1]] & m)) {
                        p[n] = t;
                        bestn = solve(p, n + 1, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[16] = {0};
    solve(path, 1, sizeof(path) / sizeof(*path));
    return 0;
}
