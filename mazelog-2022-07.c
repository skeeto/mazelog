#include <stdio.h>

#define W 7
#define H 7
enum {NN, NE, EE, SE, SS, SW, WW, NW, RR};
static const char grid[] = {
    EE, SW, SW, SW, SE, SE, WW,
    NE, WW, SW, SW, RR, SE, NW,
    NE, RR, WW, EE, SW, SW, SW,
    NE, NW, NW, SE, SW, SS, NW,
    NE, NN, NN, NW, SW, RR, SW,
    EE, NW, RR, NE, NE, SS, NN,
    NE, NE, NE, NW, EE, SW, 00,
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int v, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]];
        a = a==RR ? (v+4)%8 : a;
        for (int d = 1; ; d++) {
            int xx = x + d*moves[a*2 + 0];
            int yy = y + d*moves[a*2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n+1] = yy*W + xx;
                bestn = solve(p, n+1, a, bestn);
            } else {
                break;
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[20] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
}
