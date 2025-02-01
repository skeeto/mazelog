#include <stdio.h>

#define W 6
#define H 6
enum {K, R, B, N, X};
static const char grid[] = {
    K, B, R, X, B, B,
    B, N, B, X, X, X,
    B, X, B, B, N, X,
    B, N, B, R, B, N,
    N, X, B, B, R, B,
    B, R, B, N, X, K
};
static const signed char moves[] = {
     8,  8,  8,  4, 16,  4, 24,  8,
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
    -2, -1, -2, +1, +2, -1, +2, +1,
    -1, -2, -1, +2, +1, -2, +1, +2,
};

static int solve(int *p, int n, int last, char mark[][W], int bestn)
{
    //for (int i = 0; i <= n; i++) printf("%d%c", p[i] + 1, " \n"[i == n]);
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int c = grid[p[n]]==X ? last : grid[p[n]];
        int off = moves[c * 2 + 0];
        int len = moves[c * 2 + 1];
        const signed char *m = moves + off;
        for (int i = 0; i < len; i++) {
            int xx = x + m[i * 2 + 0];
            int yy = y + m[i * 2 + 1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = p[n+1] = xx + yy*W;
                if (grid[t]==X || !mark[yy][xx]) {
                    mark[yy][xx] = 1;
                    bestn = solve(p, n+1, c, mark, bestn);
                    mark[yy][xx] = 0;
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int  path[24]   = {0};
    char mark[H][W] = {0};
    solve(path, 0, grid[0], mark, sizeof(path)/sizeof(*path));
}
