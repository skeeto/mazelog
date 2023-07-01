#include <stdio.h>

enum {A, B, C, X};

#define W 5
#define H 5
static const char grid[] = {
    A, X, X, C, X,
    X, B, X, X, C,
    C, B, A, B, X,
    X, A, X, B, B,
    A, X, X, X, A
};
static const signed char moves[] = {
    +1, +0, +0, +1, -1, +0, +0, -1
};

static int solve(int *p, int n, int last, int bestn)
{
    if (p[n] == H*W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int b = (last + 2) % 4;
        int v = (n + 1)%3;
        for (int i = 0; i < 4; i++) {
            if (i != b) {
                int xx = x + moves[i*2 + 0];
                int yy = y + moves[i*2 + 1];
                if (xx>=0 && xx<W && yy>=0 && yy<H) {
                    int t = xx + yy * W;
                    int d = grid[t];
                    if (d==X || d==v) {
                        p[n + 1] = t;
                        bestn = solve(p, n+1, i, bestn);
                    }
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[31] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
    return 0;
}
