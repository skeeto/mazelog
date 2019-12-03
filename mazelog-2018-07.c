#include <stdio.h>

enum {B=0x01, R=0x02, S=0x10, D=0x20, X=0x30, T=0x40, C=0x80};

#define BEG  2
#define END 22
#define W    5
#define H    5
static const unsigned char grid[] = {
    0|0|0, 0|0|0, 0|B|S, 0|0|0, 0|0|0,
    0|0|0, 0|R|T, C|B|X, C|R|D, 0|0|0,
    0|B|X, 0|B|T, 0|R|D, C|B|D, C|B|S,
    0|0|0, C|B|S, 0|R|X, 0|R|S, 0|0|0,
    0|0|0, 0|0|0, 0|0|D, 0|0|0, 0|0|0
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int d, int bestn)
{
    if (p[n] == END) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int o = d % 2;
        int a = grid[p[n]];
        int c = a & 0x07;
        int s = a & 0x70;
        if (a & C)
            o = !o;
        for (int i = 0; i < 4; i++) {
            int j = i * 2 + o;
            if (j != (d + 4) % 8) { // no u-turns
                for (int v = 1; ; v++) {
                    int xx = x + v * moves[j * 2 + 0];
                    int yy = y + v * moves[j * 2 + 1];
                    if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                        int ti = yy * W + xx;
                        int ta = grid[ti];
                        int tc = ta & 0x07;
                        int ts = ta & 0x70;
                        if (tc == c || ts == s) {
                            p[n + 1] = ti;
                            bestn = solve(p, n + 1, j, bestn);
                        }
                    } else {
                        break;
                    }
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[14] = {BEG};
    solve(path, 0, 3, sizeof(path) / sizeof(*path));
}
