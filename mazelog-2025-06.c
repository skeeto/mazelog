#include <stdio.h>

#define W 4
#define H 3
enum {NN, NE, EE, SE, SS, SW, WW, NW};
static const char grid[] = {
    EE, EE, SE, SW,
    SS, WW, NE, SW,
    EE, NN, NW,  0,
};
static const int moves[] = {
    +0,-1, +1,-1, +1,+0, +1,+1, +0,+1, -1,+1, -1,+0, -1,-1
};

static int solve(int *p, int n, int v, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]];
        for (int d = v?v:1; v?d==v:1; d++) {
            int xx = x + d*moves[a*2 + 0];
            int yy = y + d*moves[a*2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n+1] = yy*W + xx;
                bestn = solve(p, n+1, v?0:d, bestn);
            } else {
                break;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[20] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
}
