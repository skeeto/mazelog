#include <stdio.h>

enum {NN, SS, EE, WW, SE, NW, NE, SW};
enum {B = 0x00, R = 0x10};

#define W 6
#define H 6
static const char grid[] = {
    B|EE, R|EE, B|SE, R|SE, R|SS, B|SW,
    R|SE, R|EE, B|WW, R|SW, B|NN, R|SW,
    R|EE, R|SE, R|NE, B|SS, B|NN, B|WW,
    R|NN, R|NE, B|WW, R|EE, R|EE, R|NW,
    R|EE, R|SW, R|SE, B|SS, R|NW, B|NN,
    R|EE, B|NN, B|EE, B|NE, B|NE, 0
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
        int v = grid[p[n]] & 0x0f;
        int t = n % 3 < 2;
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int i = yy * W + xx;
                int c = grid[i] >> 4;
                if (i == W * H - 1 || c == t) {
                    /* No looping */
                    int valid = 1;
                    for (int j = n - 2; valid && j >= 0; j -= 3)
                        if (p[j] == i)
                            valid = 0;
                    if (valid) {
                        p[n + 1] = i;
                        bestn = solve(p, n + 1, bestn);
                    }
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
    int path[28] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
}
