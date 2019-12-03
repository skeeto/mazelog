#include <stdio.h>
#include <stdlib.h>

#define W 6
#define H 5
static const signed char grid[] = {
    +9, +1, -2, -2, -1, +1,
    -1, +1, +1, +1, +1, +3,
    -2, -1, +0, +1, +3, -1,
    +1, -1, -3, +1, -1, -3,
    -2, -3, +2, +1, +3, +0
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
};

static int
solve(int *p, int n, int d, int bestn)
{
    if (p[n] == H * W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int j = d + grid[p[n]];
        if (j > 0) {
            for (int i = 0; i < 4; i++) {
                int xx = x + j * moves[i * 2 + 0];
                int yy = y + j * moves[i * 2 + 1];
                if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                    p[n + 1] = xx + yy * W;
                    bestn = solve(p, n + 1, j, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[34] = {0};
    solve(path, 0, -6, sizeof(path) / sizeof(*path));
    return 0;
}
