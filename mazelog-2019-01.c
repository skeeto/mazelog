#include <stdio.h>

enum {NN, NE, EE, SE, SS, SW, WW, NW, RR};

#define W 6
#define H 6
static const char grid[] = {
    EE, SW, SE, SE, SS, SW,
    EE, NE, RR, SE, EE, WW,
    SE, NE, EE, SE, RR, SW,
    EE, RR, SE, NE, SW, NW,
    SE, SS, NN, RR, NE, SW,
    NE, WW, WW, EE, NN, 0
};
static const int moves[] = {
    +0, -1,
    +1, -1,
    +1, +0,
    +1, +1,
    +0, +1,
    -1, +1,
    -1, +0,
    -1, -1
};

static int
solve(int *p, int n, int bestn, int dir)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        if (v == RR) v = (dir + 4) % 8;
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = yy * W + xx;
                bestn = solve(p, n + 1, bestn, v);
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
    int path[15] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path), 0);
}
