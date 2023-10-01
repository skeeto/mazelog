#include <stdio.h>

enum {D, S, C, P, X, A};

#define H 6
#define W 6
static const signed char grid[] = {
    C, S, X, C, D, C,
    C, C, P, D, S, X,
    C, P, S, X, C, D,
    C, D, C, S, X, A,
    X, S, S, S, S, P,
    C, X, D, A, P, C
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i < n; i++) {
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 4; i++) {
            for (int v = 1;; v++) {
                int tx = x + v*moves[i*2 + 0];
                int ty = y + v*moves[i*2 + 1];
                if (tx>=0 && tx<W && ty>=0 && ty<H) {
                    int s = p[n];
                    int t = ty*W + tx;
                    if ((n&1) ^ (grid[t]==grid[s])) {
                        p[n+1] = t;
                        bestn = solve(p, n+1, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[18] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
