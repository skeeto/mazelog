#include <stdio.h>

#define W 5
#define H 5
enum {S, X, P, D, C};
enum {B=0x10, R=0x20, G=0x30, V=0x40, Y=0x50};
static const char grid[] = {
    S|B, X|R, S|R, P|G, D|Y,
    D|R, P|Y, X|R, C|V, P|Y,
    S|G, S|V, P|V, D|R, X|G,
    D|R, C|B, P|B, X|G, S|Y,
    X|V, S|V, C|V, P|G, D|R,
};

static int solve(int *p, int n, int phase, char *seen, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int s = grid[p[n]] & 0x0f;
        int c = grid[p[n]] & 0xf0;
        int hv = phase < 2;
        for (int i = 0; i < W*H; i++) {
            if (i == p[n]) continue;
            int ts = grid[i] & 0x0f;
            int tc = grid[i] & 0xf0;
            if (ts!=s && tc!=c) continue;
            int dx = i%W - x;
            int dy = i/W - y;
            if (hv) {
                if (dx != 0 && dy != 0) continue;
            } else {
                if (!dx || !dy) continue;
                if (dx!=dy && dx!=-dy) continue;
            }
            int np = (phase+1)%4;
            int q = i*4 + np;
            if (!seen[q]) {
                seen[q] = 1;
                p[n+1] = i;
                bestn = solve(p, n+1, np, seen, bestn);
                seen[q] = 0;
            }
        }
    }
    return bestn;
}

int main()
{
    int path[36] = {0};
    char seen[W*H*4] = {1};
    solve(path, 0, 0, seen, sizeof(path)/sizeof(*path));
    return 0;
}
