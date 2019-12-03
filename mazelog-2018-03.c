#include <stdio.h>

#define C 0x80
enum {A=0x01, E=0x02, X=0x03, D=0x04, P=0x05, S=0x06};
enum {R=0x10, Y=0x20, B=0x30, V=0x40, O=0x50, G=0x60};

#define W 6
#define H 6
static const unsigned char grid[] = {
    0|R|A, 0|Y|E, 0|O|X, 0|O|E, 0|O|E, 0|G|E,
    C|B|A, 0|B|D, 0|V|A, 0|B|P, 0|B|E, 0|R|E,
    0|O|X, 0|R|E, 0|B|X, 0|R|X, 0|G|E, 0|O|P,
    0|Y|P, 0|B|X, C|O|A, 0|Y|A, C|O|A, 0|O|E,
    0|G|E, 0|R|E, 0|O|E, 0|V|A, 0|G|X, 0|V|A,
    0|V|A, 0|B|A, 0|G|A, C|B|A, 0|R|E, 0|O|S,
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
};

static int
solve(int *p, int n, int m, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int s = grid[p[n]] & 0x07;
        int c = grid[p[n]] & 0x70;
        for (int v = 0; v < 8; v++) {
            for (int d = 1; ; d++) {
                int tx = x + d * moves[v * 2 + 0];
                int ty = y + d * moves[v * 2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int i = ty * W + tx;
                    int ts = grid[i] & 0x07;
                    int tc = grid[i] & 0x70;
                    int to = grid[i] & 0x80;
                    if ((!m && s == ts) || (m && c == tc)) {
                        p[n + 1] = i;
                        bestn = solve(p, n + 1, to ? m : !m, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[30] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
}
