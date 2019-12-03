#include <stdio.h>

#define W 4
#define H 4
enum {P, R, B, K, X};
static const char grid[] = {
    R, B, R, P,
    B, P, B, K,
    K, P, K, P,
    R, R, B, X,
};
static const signed char moves[] = {
     0,  0,  8,  4, 16,  4, 24,  8,
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
    -2, -1, -2, +1, +2, -1, +2, +1,
    -1, -2, -1, +2, +1, -2, +1, +2,
};

static int
solve(int *p, int n, int last, int bestn)
{
    if (grid[p[n]] == X) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int c = grid[p[n]] ? grid[p[n]] : last;
        int off = moves[c * 2 + 0];
        int len = moves[c * 2 + 1];
        const signed char *m = moves + off;
        for (int i = 0; i < len; i++) {
            int xx = x + m[i * 2 + 0];
            int yy = y + m[i * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = xx + yy * W;
                bestn = solve(p, n + 1, c, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[15] = {0};
    solve(path, 0, grid[0], sizeof(path) / sizeof(*path));
}
