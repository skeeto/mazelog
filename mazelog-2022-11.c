#include <stdio.h>

#define H 6
#define W 6
enum {D, S, C, E};
static const signed char grid[] = {
    E, E, C, E, C, C,
    D, S, C, D, C, E,
    C, C, E, C, E, C,
    C, D, C, E, C, E,
    D, S, D, E, C, E,
    E, E, E, D, E, E,
};
static const signed char moves[] = {
    +1,+0, +0,+1, -1,+0, +0,-1,
};

static int
solve(int *p, int n, int d, int bestn)
{
    if (p[n-1] == W*H - 1) {
        for (int i = 0; i < n; i++) {
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1] % W;
        int y = p[n-1] / W;
        int a = grid[p[n-1]];
        int b = n>1 ? grid[p[n-2]] : -1;
        for (int i = 0; i < 4; i++) {
            if (i == d) continue;
            for (int v = 1; ; v++) {
                int tx = x + v*moves[i*2 + 0];
                int ty = y + v*moves[i*2 + 1];
                if (tx>=0 && tx<W && ty>=0 && ty<H) {
                    int t = ty*W + tx;
                    if (grid[t]!=a && grid[t]!=b) {
                        p[n] = t;
                        bestn = solve(p, n+1, (i+2)%4, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[23] = {0};
    solve(path, 1, -1, sizeof(path)/sizeof(*path));
    return 0;
}
