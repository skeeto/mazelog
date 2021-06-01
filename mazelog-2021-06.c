#include <stdio.h>

enum {G=0x10, B=0x20, R=0x30, V=0x40, Y=0x50, O=0x60};
enum {D=0x01, S=0x02, C=0x03, E=0x04};

#define H 6
#define W 6
static const signed char grid[] = {
    E|Y, D|G, D|O, D|V, C|V, S|O,
    C|O, C|G, S|G, E|B, C|R, C|G,
    E|R, C|B, E|V, C|R, D|B, S|O,
    D|G, E|R, D|G, E|B, S|V, C|B,
    D|G, E|G, C|G, S|R, E|O, S|B,
    D|B, C|V, E|G, S|B, C|G, D|R,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n-1] == W*H - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1] % W;
        int y = p[n-1] / W;
        int m = n % 2 ? 0x0f : 0xf0;
        for (int i = 0; i < 8; i++) {
            for (int v = 1; ; v++) {
                int tx = x + v*moves[i*2 + 0];
                int ty = y + v*moves[i*2 + 1];
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
    int path[23] = {0};
    solve(path, 1, sizeof(path) / sizeof(*path));
    return 0;
}
