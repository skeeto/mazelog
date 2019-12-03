#include <stdio.h>

#define W 5
#define H 5
enum {R = 0x10, G = 0x20, B = 0x30, V = 0x40, Y = 0x50};
enum {C = 0x01, D = 0x02, X = 0x03, S = 0x04, E = 0x05};
static const char grid[] = {
    R|C, B|D, B|E, G|S, G|C,
    G|S, 0|0, B|E, V|C, R|X,
    V|E, R|X, G|C, B|E, B|X,
    Y|C, B|E, V|D, R|S, G|C,
    B|E, 0|0, 0|0, R|X, Y|S
};
static const int moves[] = {+0, -1, +0, +1, +1, +0, -1, +0};

static int
solve(int *p, int n, int prev, long seen, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]] ? grid[p[n]] : prev;
        int s = v & 0x0f;
        int c = v & 0xf0;
        for (int i = 0; i < 4; i++) {
            for (int d = 1; ; d++) {
                int xx = x + d * moves[i * 2 + 0];
                int yy = y + d * moves[i * 2 + 1];
                int j = yy * W + xx;
                if (xx < 0 || xx >= W || yy < 0 || yy >= H)
                    break;
                long bit = 1L << j;
                if (grid[j] && (bit & seen))
                    continue;
                int t = grid[j];
                if (!t || (t & 0x0f) == s || (t & 0xf0) == c) {
                    p[n + 1] = yy * W + xx;
                    bestn = solve(p, n + 1, v, seen | bit, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[31] = {0};
    solve(path, 0, 0, 1L << 0, sizeof(path) / sizeof(*path));
}
