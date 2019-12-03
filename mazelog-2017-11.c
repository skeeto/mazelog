#include <stdio.h>

#define W 6
#define H 6
static const char grid[] = {
    3, 2, 2, 2, 2, 3,
    2, 3, 3, 1, 1, 1,
    3, 1, 2, 2, 3, 2,
    2, 3, 2, 2, 3, 1,
    3, 3, 2, 1, 2, 3,
    2, 1, 2, 1, 2, 1,
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
        int d = grid[p[n]];
        const int *m = moves + (n % 2) * 8;
        for (int i = 0; i < 4; i++) {
            int xx = x + d * m[i * 2 + 0];
            int yy = y + d * m[i * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = yy * W + xx;
                bestn = solve(p, n + 1, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[20] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
