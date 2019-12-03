#include <stdio.h>

#define W 5
#define H 5
static const unsigned long grid = 0x848824;
static const int moves[] = {+0, -1, +0, +1, +1, +0, -1, +0};

static int
solve(int *p, int n, int d, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (d > 0 && n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int m = 0; m < 4; m++) {
            int xx = x + d * moves[m * 2 + 0];
            int yy = y + d * moves[m * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int i = yy * W + xx;
                int f = (grid >> i) & 1UL;
                int dd;
                p[n + 1] = i;
                if (i == 0)
                    dd = 1;
                else
                    dd = f ? d + 1: d - 1;
                bestn = solve(p, n + 1, dd, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[20] = {0};
    solve(path, 0, 1, sizeof(path) / sizeof(*path));
}
