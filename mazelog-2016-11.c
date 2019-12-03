#include <stdio.h>

#define H      5
#define W      6
#define TARGET (W * H - 1)
static const signed char grid[] = {
    +3, +0, +1, +1, -2, +1,
    +1, -1, +1, +0, +1, +2,
    +1, +1, -1, -1, +2, +1,
    +1, -1, +0, +2, -2, +1,
    +0, -1, +3, -3, +2, +0,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n - 1] == TARGET) {
        /* Found a solution. */
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        for (int i = 0; i < (int)(sizeof(moves) / sizeof(*moves) / 2); i++) {
            int x = p[n - 1] % W;
            int y = p[n - 1] / W;
            int tx = x + moves[i * 2 + 0] * v;
            int ty = y + moves[i * 2 + 1] * v;
            int t = ty * W + tx;
            if (tx == 0 && ty == 0) {
                /* Special rule: (0, 0) resets the value. */
                p[n] = 0;
                bestn = solve(p, n + 1, grid[0], bestn);
            } else if (tx >= 0 && tx < W &&
                       ty >= 0 && ty < H && 
                       grid[t] + v >= 0) {
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
    int path[24] = {0};
    solve(path, 1, grid[0], sizeof(path) / sizeof(*path));
    return 0;
}
