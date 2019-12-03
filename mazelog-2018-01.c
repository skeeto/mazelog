#include <stdio.h>

enum {NN, SS, EE, WW, SE, NW, NE, SW};

#define W 8
#define H 8
static const char grid[] = {
    SS, EE, EE, SE, EE, SW, WW, WW,
    NE, NE, SS, EE, SE, SE, NE, NW,
    NE, NW, WW, SW, SW, SE, WW, NW,
    NE, NE, NW, SE, EE, SS, NE, NN,
    SE, WW, SS, EE, WW, EE, SS, SW,
    NE, WW, NN, SE, SE, NE, SS, SS,
    SE, NN, NN, NW, SS, NE, WW, NW,
    NN, WW, NE, NE, NW, WW, NW, -1,
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = yy * W + xx;
                bestn = solve(p, n + 1, bestn);
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
    int path[13] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
