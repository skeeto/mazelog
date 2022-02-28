#include <stdio.h>

#define H 3
#define W 3
#define D 3
static const signed char grid[] = {
    +1, +0, -1,  
    -1, -1, +0,  
    +1, -1, -1,  

    -1, -1, -1,
    -1, +0, +1,
    -1, +1, +1,

    +1, +1, +0, 
    -1, -1, +1, 
    -1, +1, +0, 
};
static const signed char moves[] = {
    -1, +0, +0,
    +1, +0, +0,
    +0, -1, +0,
    +0, +1, +0,
    +0, +0, +1,
    +0, +0, -1,
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n - 1] == W*H*D - 1) {
        for (int i = 0; i < n; i++)
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n-1]     % W;
        int y = p[n-1] / W % D;
        int z = p[n-1] / (W*D);
        for (int i = 0; i < 6; i++) {
            int tx = x + v*moves[i*3 + 0];
            int ty = y + v*moves[i*3 + 1];
            int tz = z + v*moves[i*3 + 2];
            if (tx >= 0 && tx < W && ty >= 0 && ty < H && tz >= 0 && tz < D) {
                int t = tz*W*D + ty*W + tx;
                if (grid[t]+v >= 0) {
                    p[n] = t;
                    bestn = solve(p, n+1, grid[t]+v, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[24] = {0};
    solve(path, 1, 1, sizeof(path) / sizeof(*path));
    return 0;
}
