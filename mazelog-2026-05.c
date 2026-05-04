#include <stdio.h>

#define W 4
#define H 4

enum { S=0x10, P=0x20, X=0x30, D=0x40 };
enum { K=0x01, V=0x02, C=0x03, O=0x04 };
#define R 0x80

static const unsigned char grid[] = {
    S|K,    P|V|R,  X|V|R,  S|V,
    S|V,    P|C,    P|V,    P|V,
    X|K|R,  P|C,    S|V|R,  D|V|R,
    S|K|R,  S|C,    S|C|R,  P|O,
};
static const signed char moves[] = {
    +0, -1, +0, +1, -1, +0, +1, +0,
};

static int solve(int *p, int n, int mode, char *visited, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int mask = mode ? 0x0f : 0x70;
        int src = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            for (int v = 1; ; v++) {
                int xx = x + v*moves[i*2 + 0];
                int yy = y + v*moves[i*2 + 1];
                if (xx<0 || xx>=W || yy<0 || yy>=H) {
                    break;
                }
                int t = yy*W + xx;
                int g = grid[t];
                if (((g ^ src) & mask) == 0) {
                    int nm = (g & R) ? !mode : mode;
                    int q = t*2 + nm;
                    if (!visited[q]) {
                        visited[q] = 1;
                        p[n+1] = t;
                        bestn = solve(p, n+1, nm, visited, bestn);
                        visited[q] = 0;
                    }
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[15] = {0};
    char visited[W*H*2] = {1};
    solve(path, 0, 0, visited, sizeof(path)/sizeof(*path));
}
