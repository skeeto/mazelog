#include <stdio.h>

enum { C, T, I, S };
#define H 3
#define W 3
#define D 3
static const unsigned char grid[] = {
    C, T, C,
    C, C, I,
    S, C, C,

    T, S, T,
    C, S, C,
    T, T, S,

    T, S, S,
    I, I, S,
    S, S, S,
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
    if (p[n-1] == W*H*D - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1]     % W;
        int y = p[n-1] / W % D;
        int z = p[n-1] / (W*D);
        int a =       grid[p[n-1]]     ;
        int b = n>1 ? grid[p[n-2]] : -1;
        for (int i = 0; i < 6; i++) {
            for (int d = 1; ; d++) {
                int tx = x + d*moves[i*3 + 0];
                int ty = y + d*moves[i*3 + 1];
                int tz = z + d*moves[i*3 + 2];
                if (tx >= 0 && tx < W &&
                    ty >= 0 && ty < H &&
                    tz >= 0 && tz < D) {
                    int t = tz*W*D + ty*W + tx;
                    if (grid[t] != a && grid[t] != b) {
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
    int path[22] = {0};
    solve(path, 1, sizeof(path) / sizeof(*path));
    return 0;
}
