#include <stdio.h>

enum {NN, SS, EE, WW, SE, NW, NE, SW, BB=0x08, SET=0x10};

#define W 6
#define H 6
static const char grid[] = {
    EE, SW, SW, SW, WW, WW,
    NE, SW, SE, SW, WW, SS,
    NE, SW, SS, WW, BB, NW,
    SE, BB, NN, NN, NE, WW,
    NN, NE, WW, BB, NE, NW,
    EE, NN, NN, NN, NN, -1,
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
};

static int solve(int *p, int n, char *cache, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]] | cache[p[n]];
        if ((v&(BB|SET)) == BB) {
            for (int i = 0; i < 8; i++) {
                cache[p[n]] = (char)i | SET;
                bestn = solve(p, n, cache, bestn);
            }
            cache[p[n]] = 0;
        } else {
            v &= 7;
            for (int d = 1; ; d++) {
                int xx = x + d*moves[v*2 + 0];
                int yy = y + d*moves[v*2 + 1];
                if (xx>=0 && xx<W && yy>=0 && yy<H) {
                    p[n+1] = yy*W + xx;
                    bestn = solve(p, n+1, cache, bestn);
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
    int path[13] = {0};
    char cache[W*H] = {0};
    solve(path, 0, cache, sizeof(path)/sizeof(*path));
}
