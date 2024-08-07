#include <stdio.h>

#define W 5
#define H 5
enum {D='@', L='.'};
static const char grid[] = {
    0, 0, L, 0, 0,
    0, L, L, L, 0,
    D, D, D, L, L,
    0, D, D, D, 0,
    0, 0, D, 0, 0,
};
static const signed char moves[] = {
    -2,-1, -2,+1, +2,-1, +2,+1, -1,-2, -1,+2, +1,-2, +1,+2
};
static const char opt[] = ".@..@@...@@@....@@@@.....@@@@@......";

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == 14) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 8; i++) {
            int xx = x + moves[i*2+0];
            int yy = y + moves[i*2+1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = yy*W + xx;
                if (grid[t] == opt[n+1]) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[30] = {2};
    solve(path, 0, sizeof(path)/sizeof(*path));
}
