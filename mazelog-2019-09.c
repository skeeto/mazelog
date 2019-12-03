#include <stdio.h>

enum {S = 0x01, C = 0x02, D = 0x03, X = 0x04, P = 0x05};
enum {V = 0x10, O = 0x20, Y = 0x30, R = 0x40, B = 0x50};

#define W 5
#define H 5
static const char grid[] = {
    V|S, O|D, Y|X, R|S, B|D,
    V|D, B|X, O|D, Y|X, O|D,
    B|X, O|D, R|C, O|P, R|D,
    R|S, Y|D, O|C, O|P, O|D,
    R|D, O|D, O|S, O|D, Y|X,
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int s = grid[p[n]] & 0x0f;
        int c = grid[p[n]] & 0xf0;
        int t = n % 6 < 3 ? 0 : 8;
        for (int i = 0; i < 4; i++) {
            for (int d = 1; ; d++) {
                int xx = x + d * moves[t + i * 2 + 0];
                int yy = y + d * moves[t + i * 2 + 1];
                if (xx < 0 || xx >= W || yy < 0 || yy >= H) {
                    break;
                }
                int i = yy * W + xx;
                int ts = grid[i] & 0x0f;
                int tc = grid[i] & 0xf0;
                if (s == ts || c == tc) {
                    p[n + 1] = i;
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
    int path[11] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
