#include <stdio.h>
#include <stdlib.h>

#define W 8
#define H 7
static const char grid[] = {
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    0, 2, 0, 1, 1, 1, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
    1, 2, 0, 1, 0, 2, 2, 1,
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 1, 2, 2, 2, 2
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, -1, -1, +1, +1, +1
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int d = grid[p[n]];
        for (int i = 0; i < 8; i++) {
            int xx = x + d*moves[i*2 + 0];
            int yy = y + d*moves[i*2 + 1];
            int t  = xx + yy*W;
            if (xx>=0 && xx<W && yy>=0 && yy<H && grid[t]) {
                p[n+1] = t;
                bestn = solve(p, n+1, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[15] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
