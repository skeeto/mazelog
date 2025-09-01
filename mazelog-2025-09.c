#include <stdio.h>

enum {D=1, S, C};

#define BEG  3
#define END 45
#define W    7
#define H    7
static const unsigned char grid[] = {
    0, 0, 0, D, 0, 0, 0,
    0, 0, S, D, D, 0, 0,
    0, D, S, D, S, C, 0,
    D, S, D, D, C, C, C,
    0, D, S, D, D, D, 0,
    0, 0, D, D, D, 0, 0,
    0, 0, 0, D, 0, 0, 0,
};
static const int moves[] = {
    +0, +1, -1, +1, -1, +0, -1, -1, +0, -1, +1, -1, +1, +0, +1, +1,
};

static int solve(int *p, int n, int d, int bestn)
{
    if (p[n] == END) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]];
        int b = n ? grid[p[n-1]] : 0;
        for (int i = 0; i < 8; i++) {
            if (i == (d + 4) % 8) continue; // no u-turns
            for (int v = 1; ; v++) {
                int tx = x + v*moves[i*2 + 0];
                int ty = y + v*moves[i*2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int ti = ty*W + tx;
                    int c = grid[ti];
                    if (c && c != a && c != b) {
                        p[n+1] = ti;
                        bestn = solve(p, n+1, i, bestn);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[10] = {BEG};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
}
