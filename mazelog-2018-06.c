#include <stdio.h>

enum {EE = 0, NL = 1, SS = 2, NR = 3};

#define W 6
#define H 6
static const char grid[] = {
     EE, NL, NR, SS, SS, NR,
     NL, NL, NR, NR, SS, NR,
     NL, NL, NL, NR, NR, NR,
     SS, NL, NL, NL, NR, NR,
     NL, SS, SS, NL, NL, NL,
     NR, NL, SS, NL, NL, EE
};
static const int moves[] = {
    +0, -1, +1, +0, +0, +1, -1, +0,
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int a = grid[yy * W + xx];
                if (a != SS) {
                    p[n + 1] = yy * W + xx;
                    bestn = solve(p, n + 1, (v + a) % 4, bestn);
                }
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
    int path[25] = {0};
    solve(path, 0, 1, sizeof(path) / sizeof(*path));
}
