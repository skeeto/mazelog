#include <stdio.h>

enum {NN, NE, EE, SE, SS, SW, WW, NW};

#define W 6
#define H 6
static const char grid[] = {
    EE, SS, WW, SW, NW, WW,
    SE, NE, NE, EE, WW, NE,
    WW, NN, SS, NE, NN, WW,
    SE, SW, NN, NN, NW, EE,
    EE, SW, WW, SE, NW, EE,
    NN, SS, NN, WW, NE, 0
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
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
        int a = grid[p[n]];
        int r = n % 2 ? -1 : 1;
        for (int d = 1; ; d++) {
            int xx = x + r * d * moves[a * 2 + 0];
            int yy = y + r * d * moves[a * 2 + 1];
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
    int path[31] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
