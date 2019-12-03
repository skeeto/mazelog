#include <stdio.h>

#define C 0x80
enum {NN, NE, EE, SE, SS, SW, WW, NW};
enum {B=0x10, R=0x20, P=0x40};

#define W 6
#define H 6
static const unsigned char grid[] = {
    0|B|EE, 0|R|SE, 0|R|NE, 0|B|EE, 0|R|EE, 0|P|SW,
    0|R|SE, 0|B|WW, 0|B|SS, 0|P|NN, 0|B|SW, 0|B|NW,
    0|P|NN, C|B|EE, 0|P|SW, 0|R|NW, 0|P|SW, 0|B|NN,
    0|R|WW, 0|R|NW, 0|B|SS, 0|B|SE, 0|R|SS, 0|B|NW,
    0|B|SE, 0|R|NE, C|R|EE, 0|P|NE, C|R|NE, 0|B|NE,
    0|B|NE, 0|R|WW, 0|R|NE, 0|P|SW, 0|R|EE, 0

};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

static int
solve(int *p, int n, int r, int bestn)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]] & 0x0f;
        int c = grid[p[n]] & 0x70;
        if (r) v = (v + 4) % 8;
        for (int d = 1; ; d++) {
            int xx = x + d * moves[v * 2 + 0];
            int yy = y + d * moves[v * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                static char seen[2][W*H];
                int i = yy * W + xx;
                int cc = grid[i] & 0x70;
                if (!seen[r][i] && cc != c) {
                    int rr = grid[i] & 0x80 ? !r : r;
                    p[n + 1] = i;
                    seen[r][i] = 1;
                    bestn = solve(p, n + 1, rr, bestn);
                    seen[r][i] = 0;
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
    int path[23] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
}
