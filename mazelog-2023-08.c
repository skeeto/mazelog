#include <stdio.h>
#include <stdlib.h>

#define W 5
#define H 5
static const char grid[] = {
    2, 2, 1, 0, 0,
    2, 1, 1, 1, 0,
    1, 1, 3, 3, 3,
    0, 1, 2, 3, 1,
    0, 0, 3, 2, 5
};
static const signed char moves[] = { -1,+0, +1,+0, +0,-1, +0,+1 };

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
        int e = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            for (int d = 1; d <= 4; d++) {
                if (n%2 ? e==d : e!=d) continue;
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
    int path[16] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
