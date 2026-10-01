#include <stdio.h>

#define W 6
#define H 5
static const char grid[] = {
    2, 1, 3, 2, 1, 2,
    1, 3, 2, 3, 1, 1,
    2, 3, 3, 3, 3, 3,
    2, 1, 1, 2, 1, 3,
    3, 3, 2, 2, 1, 0,
};
static const signed char moves[] = {
    -1,0, +1,0, 0,-1, 0,+1, -1,-1, -1,+1, +1,-1, +1,+1
};

static int solve(int *p, int n, int phase, char *seen, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        int base = (phase == 0) ? 0 : 8;
        for (int i = 0; i < 4; i++) {
            int xx = x + v*moves[base + i*2 + 0];
            int yy = y + v*moves[base + i*2 + 1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = yy*W + xx;
                int np = (phase+1)%3;
                int q = t*3 + np;
                if (!seen[q]) {
                    seen[q] = 1;
                    p[n+1] = t;
                    bestn = solve(p, n+1, np, seen, bestn);
                    seen[q] = 0;
                }
            }
        }
    }
    return bestn;
}

int main()
{
    int path[29] = {0};
    char seen[W*H*3] = {1};
    solve(path, 0, 0, seen, sizeof(path)/sizeof(*path));
    return 0;
}
