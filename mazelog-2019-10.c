#include <stdio.h>

enum {NN, NE, EE, SE, SS, SW, WW, NW};

#define W 7
#define H 5
static const char grid[] = {
    SE, SE, EE, NN, EE, SS, NE,
    EE, SW, WW, WW, WW, WW, WW,
    SE, SW, SS, WW, SS, SS, EE,
    SE, EE, SW, NN, NE, NN, NN,
    WW, NN, SE, NW, NE, NW, 0
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int bestn)
{
    static char mark[W * H];
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int b = 1 << (n % 6);
        if (mark[p[n]] & b)
            return bestn;
        mark[p[n]] ^= b;
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]];
        int r = n / 3 % 2 ? -1 : 1;
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
        mark[p[n]] ^= b;
    }
    return bestn;
}

int
main(void)
{
    int path[23] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
