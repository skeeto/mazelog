#include <stdio.h>

#define W 5
#define H 5

enum {S=0<<4, T=1<<4, X=2<<4, C=3<<4};
static const unsigned char grid[] = {
    S|3, S|3, T|2, X|2, T|2,
    T|3, C|2, T|3, X|3, S|3,
    T|1, X|3, T|3, X|2, T|3,
    S|2, T|1, T|1, X|3, C|2,
    T|2, C|2, C|2, S|3, X|0,
};
static const int moves[] = {-1, +0, +1, +0, +0, -1, +0, +1};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == H*W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (p[n] != H*W - 1 && n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        if (n % 2) {
            int s = grid[p[n]]  & 0xf0;
            for (int i = 0; i < 4; i++) {
                for (int d = 1; ; d++) {
                    int xx = x + d*moves[i*2 + 0];
                    int yy = y + d*moves[i*2 + 1];
                    if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                        int t = yy*W + xx;
                        if ((grid[t] & 0xf0) == s) {
                            p[n+1] = t;
                            bestn = solve(p, n+1, bestn);
                        }
                    } else {
                        break;
                    }
                }
            }
        } else {
            int d = grid[p[n]] &  3;
            for (int i = 0; i < 4; i++) {
                int xx = x + d*moves[i*2 + 0];
                int yy = y + d*moves[i*2 + 1];
                if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                    p[n+1] = yy*W + xx;
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
    int path[24] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
    return 0;
}
