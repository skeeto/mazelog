#include <stdio.h>

#define W 4
#define H 4
enum {NN, NE, EE, SE, SS, SW, WW, NW};
static const char grid[] = {
    EE, SW, SS, SW,
    SE, SE, NN, WW,
    SE, EE, NW, NN,
    NN, WW, WW,  0,
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int m, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        for (int d = m ? m : 1; ; d += m ? 3 : 1) {
            int xx = x + d*moves[v*2 + 0];
            int yy = y + d*moves[v*2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n+1] = yy*W + xx;
                bestn = solve(p, n + 1, m ? 0 : d, bestn);
            } else {
                break;
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[12] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
}
