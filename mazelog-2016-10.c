#include <stdio.h>

#define N 4
static const signed char grid[] = {
    +3, -1, +1, -2,
    -1, +1, -1, +2,
    -1, +0, +0, -1,
    -1, +2, +1, +0,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n - 1] == N * N - 1) {
        /* Found a solution. */
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        for (int i = 0; i < (int)(sizeof(moves) / sizeof(*moves) / 2); i++) {
            int x = p[n - 1] % N;
            int y = p[n - 1] / N;
            int tx = x + moves[i * 2 + 0] * v;
            int ty = y + moves[i * 2 + 1] * v;
            int t = ty * N + tx;
            if (tx == 0 && ty == 0) {
                /* Special rule: (0, 0) resets the value. */
                p[n] = 0;
                bestn = solve(p, n + 1, grid[0], bestn);
            } else if (tx >= 0 && tx < N && ty >= 0 && ty < N &&
                       grid[t] + v > 0 && grid[t] + v < N) {
                p[n] = t;
                bestn = solve(p, n + 1, grid[t] + v, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[16] = {0};
    solve(path, 1, grid[0], sizeof(path) / sizeof(*path));
    return 0;
}
