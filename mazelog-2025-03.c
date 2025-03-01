#include <stdio.h>
#include <stdlib.h>

#define W 7
#define H 7
static const char grid[] = {
    1, 1, 3, 2, 2, 1, 3,
    1, 2, 2, 2, 2, 2, 2,
    3, 1, 2, 4, 2, 2, 1,
    2, 2, 4, 2, 2, 2, 4,
    2, 2, 2, 3, 4, 2, 2,
    1, 2, 1, 2, 1, 2, 1,
    2, 2, 1, 4, 1, 2, 1,
};
static const signed char moves[] = { -1,+0, +0,-1, +1,+0, +0,+1, };

static int solve(int *p, int n, int d, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            int xx = x + v*moves[i*2 + 0];
            int yy = y + v*moves[i*2 + 1];
            int t  = xx + yy*W;
            if (i!=d && xx>=0 && xx<W && yy>=0 && yy<H && grid[t]) {
                p[n+1] = t;
                bestn = solve(p, n+1, (i+2)%4, bestn);
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[30] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
    return 0;
}
