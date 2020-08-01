#include <stdio.h>

#define C 0x80
enum {N=0x01, Q=0x02, X=0x03, D=0x04, T=0x05, S=0x06};
enum {R=0x10, Y=0x20, B=0x30, V=0x40, O=0x50, G=0x60};

#define W 6
#define H 6
static const unsigned char grid[] = {
    0|N|V, C|N|Y, 0|X|Y, C|T|Y, C|T|B, C|N|B,
    C|Q|V, 0|S|Y, C|S|G, 0|X|V, C|D|B, 0|X|R,
    0|T|Y, 0|T|Y, C|N|V, C|T|V, 0|T|R, 0|D|V,
    C|D|R, C|Q|V, C|D|G, 0|D|R, C|D|O, C|D|B,
    C|Q|R, 0|S|B, C|Q|R, 0|X|Y, C|T|V, C|X|R,
    C|Q|R, 0|S|R, C|D|B, 0|Q|Y, C|S|Y, 0|X|O
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0,
    +1, +1, -1, -1, +1, -1, -1, +1,
};

static int
solve(int *p, int n, int m, int bestn)
{
    static char seen[W*H][W*H];
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int s = grid[p[n]] & 0x07;
        int c = grid[p[n]] & 0x70;
        const int *o = moves + 8*m;
        for (int v = 0; v < 4; v++) {
            for (int d = 1; ; d++) {
                int tx = x + d*o[v*2 + 0];
                int ty = y + d*o[v*2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int i = ty*W + tx;
                    int ts = grid[i] & 0x07;
                    int tc = grid[i] & 0x70;
                    int to = grid[i] & 0x80;
                    int nm = to ? !m : m;
                    if (!seen[p[n]][i] && ((s == ts) || (c == tc))) {
                        p[n+1] = i;
                        seen[p[n]][i] = 1;
                        bestn = solve(p, n + 1, nm, bestn);
                        seen[p[n]][i] = 0;
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
    int path[33] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
}
