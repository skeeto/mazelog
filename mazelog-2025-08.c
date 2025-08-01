#include <stdio.h>

#define W 5
#define H 5
enum {R = 0x10, G = 0x20, B = 0x30, V = 0x40, Y = 0x50};
enum {C = 0x01, D = 0x02, X = 0x03, P = 0x04, A = 0x05, S = 0x06};
static const char grid[] = {
    B|A, B|C, Y|A, Y|P, G|X,
    Y|P, R|X, V|C, V|C, G|D,
    V|A, R|D, R|X, G|X, R|P,
    R|X, R|X, V|A, G|C, G|P,
    Y|X, B|P, B|C, V|X, Y|X,
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
};

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        int s = v & 0x0f;
        int c = v & 0xf0;
        const int *m = moves + n/2%2*8;
        for (int i = 0; i < 4; i++) {
            for (int d = 1; ; d++) {
                int xx = x + d*m[i*2 + 0];
                int yy = y + d*m[i*2 + 1];
                if (xx < 0 || xx >= W || yy < 0 || yy >= H)
                    break;
                int t = grid[yy*W + xx];
                if ((t & 0x0f) == s || (t & 0xf0) == c) {
                    p[n+1] = yy*W + xx;
                    bestn = solve(p, n+1, bestn);
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[26] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
