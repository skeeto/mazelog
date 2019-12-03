#include <stdio.h>

enum {NN, SS, EE, WW, SE, NW, NE, SW};
enum {B = 0x00, R = 0x10};

#define W 5
#define H 5
static const char grid[] = {
    B|SS, B|EE, B|EE, B|SS, R|SW,
    B|NN, R|EE, R|SW, R|SS, B|SS,
    B|SE, B|EE, R|SW, R|EE, R|WW,
    B|EE, B|SW, B|NW, R|NW, B|SW,
    B|NN, B|NN, B|WW, R|WW,    0,

};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
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
        int v = grid[p[n]] & 0x0f;
        int t = ((n + 1) / 3) & 1;
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int i = yy * W + xx;
                int c = grid[i] >> 4;
                if (c == t) {
                    p[n + 1] = i;
                    bestn = solve(p, n + 1, bestn);
                }
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
    int path[26] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
