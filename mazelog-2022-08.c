#include <stdio.h>

#define H 5
#define W 6
static const signed char grid[] = {
    +3, +0, -2, -1, -1, -1,
    -2, +1, +0, -1, -2, +0,
    +0, +3, +2, -2, -1, +2,
    +2, +0, -2, -2, -1, +1,
    +1, +2, -2, +0, -1, +0
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
    +1, +1, -1, -1, +1, -1, -1, +1
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n-1] == W*H - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1+p[i], i<n-1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1] % W;
        int y = p[n-1] / W;
        for (int i = 0; i < 8; i++) {
            int tx = x + v*moves[i*2 + 0];
            int ty = y + v*moves[i*2 + 1];
            if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                int t = ty*W + tx;
                int s = t ? grid[t]+v : grid[0];
                if (s > 0) {
                    p[n] = t;
                    bestn = solve(p, n+1, s, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[26] = {0};
    solve(path, 1, grid[0], sizeof(path) / sizeof(*path));
    return 0;
}
