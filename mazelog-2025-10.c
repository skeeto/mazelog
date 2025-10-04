#include <stdio.h>
#include <stdlib.h>

#define W 6
#define H 6
static const signed char grid[] = {
    +2, -2, +4, +1, +2, +3,
    -3, +1, +1, -4, +1, +1,
    +1, +4, +2, +4, +1, +4,
    +4, +2, +1, +3, +4, +1,
    -1, +1, +4, +1, +1, +2,
    +4, -1, +2, +3, +2, +2,
};
static const signed char moves[][8] = {
    {-1, +0, +1, +0, +0, -1, +0, +1},
    {-1, -1, +1, +1, +1, -1, -1, +1},
};

static int solve(int *p, int n, int m, int bestn)
{
    if (p[n] == H*W - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int v = abs(grid[p[n]]);
        int x = p[n] % W;
        int y = p[n] / W;
        if (grid[p[n]] < 0) {
            m = !m;
        }
        for (int i = 0; i < 4; i++) {
            int xx = x + v*moves[m][i*2 + 0];
            int yy = y + v*moves[m][i*2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n+1] = xx + yy*W;
                bestn = solve(p, n+1, m, bestn);
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[36] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
    return 0;
}
