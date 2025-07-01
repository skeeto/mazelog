#include <stdio.h>
#include <stdlib.h>

#define W 9
#define H 9
static const char grid[] = {
    3, 1, 3, 3, 5, 3, 3, 2, 3,
    3, 3, 1, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 5, 3, 2,
    2, 3, 3, 3, 5, 3, 4, 3, 3,
    3, 2, 3, 3, 3, 4, 3, 4, 3,
    4, 3, 2, 3, 3, 3, 3, 3, 3,
    2, 3, 3, 3, 3, 3, 1, 3, 3,
    3, 3, 4, 3, 3, 3, 3, 2, 3,
    1, 3, 3, 3, 3, 2, 3, 3, 3,
};
static const signed char moves[] = { -1,+0, +1,+0, +0,-1, +0,+1 };

static int solve(int *p, int n, char *v, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int d = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            int xx = x + d*moves[i*2 + 0];
            int yy = y + d*moves[i*2 + 1];
            int t  = xx + yy*W;
            if (xx>=0 && xx<W && yy>=0 && yy<H && !v[t]) {
                p[n+1] = t;
                v[t] = 1;
                bestn = solve(p, n+1, v, bestn);
                v[t] = 0;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int  path[26]  = {0};
    char seen[W*H] = {0};
    solve(path, 0, seen, sizeof(path)/sizeof(*path));
}
