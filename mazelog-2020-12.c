#include <stdio.h>

enum {C=1, V, A, X};

#define H 7
#define W 7
static const signed char grid[] = {
    0, V, V, V, A, A, C,
    V, A, A, V, A, 0, C,
    A, 0, A, 0, C, V, C,
    V, V, V, X, V, A, 0,
    A, 0, 0, A, C, C, C,
    A, 0, 0, A, A, 0, A,
    A, C, A, V, C, A, C,
};
static const signed char moves[] = {
    +1, +0, +0, +1, -1, +0, +0, -1,
};

static int
solve(int *p, int n, int d, int bestn)
{
    if (p[n - 1] == W * H / 2) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1] % W;
        int y = p[n-1] / W;
        for (int v = 1; ; v++) {
            int tx = x + v*moves[d*2+0];
            int ty = y + v*moves[d*2+1];
            if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                int ti = ty*W + tx;
                int g = grid[ti];
                if (!g || (d%2 && g == V)) continue;
                p[n] = ti;
                bestn = solve(p, n + 1, (d + g + d%2*2) % 4, bestn);
            } else {
                break;
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[30] = {0};
    solve(path, 1, 0, sizeof(path) / sizeof(*path));
    return 0;
}
