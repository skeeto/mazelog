#include <stdio.h>
#include <stdlib.h>

#define W 7
#define H 7
static const char grid[] = {
    3, 1, 3, 4, 3, 4, 0,
    2, 4, 1, 2, 1, 3, 0,
    1, 1, 1, 4, 3, 4, 0,
    2, 1, 1, 2, 1, 2, 0,
    1, 4, 3, 1, 4, 4, 0,
    3, 2, 4, 2, 1, 2, 0,
    3, 1, 1, 4, 1, 4, 0,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] % W == W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int d = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            int xx = x + d*moves[i*2 + 0];
            int yy = y + d*moves[i*2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n+1] = xx + yy*W;
                bestn = solve(p, n+1, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[19] = {21};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
