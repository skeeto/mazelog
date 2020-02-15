#include <stdio.h>

#define H 5
#define W 5
static const signed char grid[] = {
    +2, -1, -1, -2, +1,
    -1, +9, +1, +9, -1,
    -2, +0, +1, +1, -1,
    +0, +9, +1, +9, +1,
    -1, -1, -1, -1, +0
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n - 1] == W * H - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n - 1] % W;
        int y = p[n - 1] / W;
        for (int i = 0; i < 4; i++) {
            if (x % 2 == 1 && i > 1) continue;
            if (y % 2 == 1 && i < 2) continue;
            int tx = x + moves[i * 2 + 0] * v;
            int ty = y + moves[i * 2 + 1] * v;
            if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                int t = ty * W + tx;
                if (grid[t] + v >= 0) {
                    p[n] = t;
                    bestn = solve(p, n + 1, grid[t] + v, bestn);
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
