#include <stdio.h>

#define W 8
#define H 8
enum {T=1, G, B};
static const char grid[] = {
    0, 0, 0, B, B, 0, 0, 0,
    0, G, G, T, B, T, T, 0,
    0, G, T, B, G, B, B, 0,
    T, T, B, G, T, G, G, B,
    T, T, B, T, B, T, G, B,
    0, T, B, G, B, T, G, 0,
    0, G, B, G, T, T, G, 0,
    0, 0, 0, T, G, 0, 0, 0,
};
static const signed char moves[] = {
    -2,-1, -2,+1, +2,-1, +2,+1, -1,-2, -1,+2, +1,-2, +1,+2
};

static int solve(int *p, int n, int bestn)
{
    if (p[n] == 31) {
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
    int path[18] = {24};
    solve(path, 0, sizeof(path)/sizeof(*path));
}
