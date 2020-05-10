#include <stdio.h>

#define W 7
#define H 7
enum {NN, NE, EE, SE, SS, SW, WW, NW, XX};
static const char grid[] = {
    XX, SW, NW, NW, SE, NE, XX,
    SE, SE, SW, SW, NE, SS, NW,
    NE, NW, SW, SE, NE, NW, NE,
    SW, NE, NE, NN, SW, SW, WW,
    NE, NE, SW, NE, NE, NE, SW,
    WW, SS, NW, SW, SE, NW, NE,
    XX, NW, SE, NE, SE, SW, XX
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int bestn)
{
    if (grid[p[n]] == XX) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        if (n % 2) v = (v + 4) % 8;
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
    int path[12] = {24};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
