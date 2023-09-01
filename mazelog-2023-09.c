#include <stdio.h>
#include <stdlib.h>

#define W 7
#define H 7
static const char grid[] = {
    0, 0, 0, 1, 0, 0, 0,
    0, 0, 4, 5, 5, 0, 0,
    0, 3, 1, 5, 2, 3, 0,
    1, 4, 5, 5, 5, 1, 2,
    0, 3, 5, 3, 2, 4, 0,
    0, 0, 3, 4, 3, 0, 0,
    0, 0, 0, 6, 0, 0, 0
};
static const signed char moves[] = { -1,+0, +1,+0, +0,-1, +0,+1 };

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == 45) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int m = 1<<grid[p[n]] ^ -(n&1);
        for (int i = 0; i < 4; i++) {
            for (int d = 1; d <= 6; d++) {
                if (!(1<<d & m)) continue;
                int xx = x + d*moves[i*2 + 0];
                int yy = y + d*moves[i*2 + 1];
                int t  = xx + yy*W;
                if (xx>=0 && xx<W && yy>=0 && yy<H && grid[t]) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[23] = {3};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
