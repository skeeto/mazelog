#include <stdio.h>

enum {D, S, E, C};

#define H 5
#define W 5
static const signed char grid[] = {
    D, D, C, D, D,
    C, S, C, S, D,
    D, S, C, E, D,
    E, S, E, E, E,
    D, S, D, D, D,
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
        int x = p[n-1] % W;
        int y = p[n-1] / W;
        for (int i = 0; i < 4; i++) {
            for (int v = 1; ; v++) {
                int tx = x + v*moves[i*2+0];
                int ty = y + v*moves[i*2+1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    p[n] = ty*W + tx;
                    if ((n < 1 || grid[p[n-1]] != grid[p[n]]) &&
                        (n < 2 || grid[p[n-2]] != grid[p[n]])) {
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
    int path[13] = {0};
    solve(path, 1, sizeof(path) / sizeof(*path));
    return 0;
}
