#include <stdio.h>

enum {H, D, V, U, X};

#define H 5
#define W 5
static const signed char grid[] = {
    X, V, V, V, U,
    H, H, D, U, D,
    H, D, X, V, H,
    D, D, H, X, D,
    H, U, U, D, U
};
static const signed char moves[] = {+1,+0, +0,+1, -1,+0, +0,-1};

static int solve(int *p, int n, int d, int bestn)
{
    if (p[n] == 2*5+2) {
        for (int i = 0; i < n; i++) {
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int v = 1; ; v++) {
            int tx = x + v*moves[d*2+0];
            int ty = y + v*moves[d*2+1];
            if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                int ti = ty*W + tx;
                int td = d;
                switch (grid[ti]) {
                case H: if (d%2 == 0) continue; td += 2; break;
                case V: if (d%2 == 1) continue; td += 2; break;
                case D: td += 1 + d%2*2; break;
                case U: td += 3 + d%2*2; break;
                }
                p[n+1] = ti;
                bestn = solve(p, n+1, td%4, bestn);
            } else {
                break;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[17] = {0};
    solve(path, 0, 1, sizeof(path)/sizeof(*path));
    return 0;
}
