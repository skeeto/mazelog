#include <stdio.h>

enum { O=010, S=020, X=030 };
enum { B=001, G=002, P=003, V=004 };
#define H 3
#define W 3
#define D 3
static const signed char grid[] = {
    O|P, O|B, O|V,
    O|B, X|B, X|G,
    O|B, O|G, O|G,

    O|V, S|V, X|V,
    X|B, X|V, X|B,
    O|B, X|G, O|G,

    X|P, S|G, O|P,
    S|B, S|B, X|P,
    S|G, S|G, X|B,
};
static const signed char moves[] = {
    -1, +0, +0,
    +1, +0, +0,
    +0, -1, +0,
    +0, +1, +0,
    +0, +0, +1,
    +0, +0, -1,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n - 1] == W*H*D - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1]     % W;
        int y = p[n-1] / W % D;
        int z = p[n-1] / (W*D);
        int m = n&1 ? 070 : 007;
        int v = grid[p[n-1]] & m;
        for (int i = 0; i < 6; i++) {
            for (int d = 1; ; d++) {
                int tx = x + d*moves[i*3 + 0];
                int ty = y + d*moves[i*3 + 1];
                int tz = z + d*moves[i*3 + 2];
                if (tx >= 0 && tx < W &&
                    ty >= 0 && ty < H &&
                    tz >= 0 && tz < D) {
                    int t = tz*W*D + ty*W + tx;
                    if ((grid[t]&m) == v) {
                        p[n] = t;
                        bestn = solve(p, n+1, bestn);
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
    int path[19] = {0};
    solve(path, 1, sizeof(path) / sizeof(*path));
    return 0;
}
