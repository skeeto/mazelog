#include <stdio.h>

enum {A=0x01, E=0x02, X=0x03, C=0x04, P=0x05, S=0x06};
enum {R=0x10, Y=0x20, B=0x30, V=0x40, O=0x50, G=0x60};

#define W 6
#define H 6
static const unsigned char grid[] = {
    R|C, B|E, O|S, O|X, V|C, G|E,
    V|C, B|P, Y|X, G|X, Y|S, V|P,
    O|A, V|A, V|S, G|E, V|C, B|E,
    O|E, O|P, R|X, R|S, V|A, B|A,
    Y|C, O|X, B|C, Y|S, B|A, G|A,
    B|E, R|X, B|A, V|A, R|S, V|C
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int s = grid[p[n]] & 0x07;
        int c = grid[p[n]] & 0x70;
        for (int v = 0; v < 4; v++) {
            for (int d = 1; ; d++) {
                int tx = x + d * moves[v * 2 + 0];
                int ty = y + d * moves[v * 2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int i = ty * W + tx;
                    int ts = grid[i] & 0x07;
                    int tc = grid[i] & 0x70;
                    if ((!(n % 2) && s == ts) || ((n % 2) && c == tc)) {
                        p[n + 1] = i;
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
    int path[17] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
