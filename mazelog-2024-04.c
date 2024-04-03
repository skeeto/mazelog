#include <stdio.h>

#define W 6
#define H 4
enum {NN, NE, EE, SE, SS, SW, WW, NW};
static const signed char grid[] = {
    SS, WW, NN, NW, NN, SS,
    EE, SW, NE, NW, EE, WW,
    -1, WW, SW, WW, EE, -1,
    -1, EE, SE, SW, 00, -1,
};
static const int moves[] = {
    +0,-1, +1,-1, +1,+0, +1,+1,
    +0,+1, -1,+1, -1,+0, -1,-1,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 2) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int m = 1<<grid[p[n]];
        m = n%2 ? ~m: m;
        for (int v = 0; v < 8; v++) {
            if (!((1 << v)&m)) continue;
            for (int d = 1; ; d++) {
                int xx = x + d*moves[v*2 + 0];
                int yy = y + d*moves[v*2 + 1];
                if (xx>=0 && xx<W && yy>=0 && yy<H) {
                    int t = yy*W + xx;
                    if (grid[t]!=-1) {
                        p[n+1] = t;
                        bestn = solve(p, n+1, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[14] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
