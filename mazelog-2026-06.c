#include <stdio.h>

#define W 6
#define H 6
enum {T=1, G, B};
static const char grid[] = {
    T, T, B, T, B, B,
    G, G, G, T, T, B,
    B, G, T, G, G, T,
    G, G, B, G, B, T,
    B, T, B, T, T, B,
    T, B, T, G, B, G,
};
static const signed char moves[] = {
    -2,-1, -2,+1, +2,-1, +2,+1, -1,-2, -1,+2, +1,-2, +1,+2
};

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int w = 1 + (n + 1)%3;
        for (int i = 0; i < 8; i++) {
            int xx = x + moves[i*2+0];
            int yy = y + moves[i*2+1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = yy*W + xx;
                if (grid[t] == w) {
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
    int path[18] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
}
