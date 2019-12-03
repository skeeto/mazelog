#include <stdio.h>
#include <stdlib.h>

#define W 7
#define H 7
enum {UU, UR, RR, DR, DD, DL, LL, UL, TT};
static const char grid[] = {
    TT, DR, DL, DR, DD, DR, TT,
    RR, RR, DL, UL, RR, UL, LL,
    UR, UU, UU, UR, LL, LL, LL,
    DR, DR, RR, UU, DR, UR, UL,
    DR, UR, UU, RR, UU, UU, LL,
    UU, UR, DR, RR, UU, DR, DL,
    TT, UU, UR, UR, UU, UL, TT,
};
static const signed char moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1,
};

static int
solve(int *p, int n, int bestn)
{
    if (grid[p[n]] == TT) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int d = grid[p[n]];
        for (int s = 1; ; s++) {
            int xx = x + s * moves[d * 2 + 0];
            int yy = y + s * moves[d * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = xx + yy * W;
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
    return 0;
}
