#include <stdio.h>

#define W 8
#define H 8
enum {L=0x10, D=0x00};
enum {P, R, B, K, Q, X};
static const char grid[] = {
    D|K, L|B, D|R, D|R, L|R, L|R, D|R, L|B,
    D|K, L|K, D|K, L|K, D|K, L|K, L|B, D|B,
    L|B, L|K, D|B, D|K, D|R, D|K, D|R, D|K,
    D|K, L|B, D|K, L|R, D|R, L|K, L|K, L|B,
    L|B, L|B, L|R, L|R, L|R, D|R, L|B, D|R,
    D|B, L|R, L|K, L|B, L|R, L|B, L|R, D|K,
    D|K, L|B, D|K, L|K, D|B, D|R, D|R, L|B,
    D|R, L|B, D|B, L|K, D|R, L|B, L|R, D|X,
};
static const signed char moves[] = {
     0,  0, 10,  4, 18,  4, 26,  8, 42,  8,
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
    -2, -1, -2, +1, +2, -1, +2, +1,
    -1, -2, -1, +2, +1, -2, +1, +2,
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
};

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x   = p[n] % W;
        int y   = p[n] / W;
        int k   = grid[p[n]]&0x0f;
        int off = moves[k*2 + 0];
        int len = moves[k*2 + 1];
        const signed char *m = moves + off;
        for (int i = 0; i < len; i++) {
            int xx = x + m[i*2 + 0];
            int yy = y + m[i*2 + 1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t  = xx + yy*W;
                int c  = grid[t] >> 4;
                int tc = (n + 1) / 2 % 2;
                if (c == tc) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, bestn);
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[53] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
}
