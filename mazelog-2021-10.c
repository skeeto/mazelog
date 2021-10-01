#include <stdio.h>

#define W 5
#define H 4
enum {D, U, V, Z};
static const char grid[] = {
    D, Z, U, V, Z,
    V, U, U, U, V,
    D, D, V, U, Z,
    D, U, V, Z, 0,
};
static const int moves[] = {+1, +1, +1, -1, +0, +1, +1, +0};

static int
solve(int *p, int n, int last, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = n&1 ? last : 1;
        int b = n&1 ? last : 4;
        int c = grid[p[n]];
        for (int d = a; d <= b; d++) {
            for (int v = -1; v <= +1; v += 2) {
                int xx = x + v*d*moves[c*2 + 0];
                int yy = y + v*d*moves[c*2 + 1];
                if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                    p[n+1] = xx + yy*W;
                    bestn = solve(p, n+1, d, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[26] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
}
