#include <stdio.h>

#define W 6
#define H 6
enum {P, R, B, K};
enum {D, L = 0x10};
static const char grid[] = {
    D|B, L|K, L|K, L|B, D|K, D|B,
    L|K, D|K, L|B, L|B, D|K, D|R,
    D|K, L|K, L|K, L|K, D|K, D|K,
    L|B, L|K, L|K, L|K, D|K, L|K,
    L|K, D|B, D|B, L|B, D|K, D|K,
    L|B, L|B, L|K, D|K, L|K, L|K
};
static const signed char moves[] = {
     0,  0,  8,  4, 16,  4, 24,  8,
    -1, +0, +1, +0, +0, -1, +0, +1,
    -1, -1, +1, +1, -1, +1, +1, -1,
    -2, -1, -2, +1, +2, -1, +2, +1,
    -1, -2, -1, +2, +1, -2, +1, +2,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int g = (n+1) / 2 % 2;
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]] & 0x0f;
        int off = moves[v * 2 + 0];
        int len = moves[v * 2 + 1];
        const signed char *m = moves + off;
        for (int i = 0; i < len; i++) {
            int xx = x + m[i * 2 + 0];
            int yy = y + m[i * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int t = yy * W + xx;
                if (grid[t] >> 4 == g) {
                    p[n + 1] = t;
                    bestn = solve(p, n + 1, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[27] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
