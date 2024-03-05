#include <stdio.h>

enum {D, S, C, P, X, A};

#define H 5
#define W 5
static const signed char grid[] = {
    C, C, X, D, P,
    X, P, C, S, S,
    S, C, D, P, C,
    P, A, S, X, D,
    D, D, P, C, S,
};
static const signed char moves[] = {
    +1,+0, +1,+1, +0,+1, -1,+1, -1,+0, -1,-1, +0,-1, +1,-1,
};

static int solve(int *p, int n, int bestn, int b)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", 1+p[i], i<n?' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 8; i++) {
            for (int v = 1;; v++) {
                int tx = x + v*moves[i*2 + 0];
                int ty = y + v*moves[i*2 + 1];
                if (i!=b && tx>=0 && tx<W && ty>=0 && ty<H) {
                    int s = p[n];
                    int t = ty*W + tx;
                    if ((n&1) ^ (grid[t]==grid[s])) {
                        p[n+1] = t;
                        bestn = solve(p, n+1, bestn, (i+4)%8);
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
    int path[15] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path), -1);
    return 0;
}
