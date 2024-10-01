#include <stdio.h>

enum {D=0x01, S=0x02, C=0x03, X=0x04, T=0x05, U=0x06, P=0x07};
enum {B=0x10, G=0x20, V=0x30, Y=0x40, R=0x50};
enum {H=5, W=5};
static const signed char grid[] = {
    G|X, B|T, V|S, G|D, R|C,
    R|D, G|T, R|D, B|C, V|S,
    V|X, Y|U, G|C, V|D, B|U,
    B|S, Y|P, V|S, R|U, Y|X,
    V|S, R|S, G|D, G|X, Y|P,
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
};
static const char opt[] = " @  @@   @@@    @@@@     @@@@@      @@@@@@";

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", 1+p[i], i<n ? ' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 4; i++) {
            for (int v = 1;; v++) {
                int s = opt[n]=='@' ? 8 : 0;
                int tx = x + v*moves[s + i*2 + 0];
                int ty = y + v*moves[s + i*2 + 1];
                if (tx>=0 && tx<W && ty>=0 && ty<H) {
                    int t = ty*W + tx;
                    int m = grid[p[n]] ^ grid[t];
                    if (!(m&0xf0) || !(m&0x0f)) {
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
    int path[17] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
