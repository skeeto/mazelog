#include <stdio.h>

#define W 5
#define H 5
enum direction { UU, UR, RR, DR, DD, DL, LL, UL };
static const char grid[] = {
    RR, DL, DR, DL, LL,
    UU, LL, DL, DL, LL,
    DR, DR, UL, UL, UR,
    UR, LL, UR, DR, DD,
    DL, DD, DR, UL, 0
};
static const signed char moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == H * W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int v = (grid[p[n]] + n % 4 / 2 * 4) % 8;
        int x = p[n] % W;
        int y = p[n] / W;
        for (int d = 1; d < W; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = xx + yy * W;
                bestn = solve(p, n + 1, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[24] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
    return 0;
}
