#include <stdio.h>

#define W 5
#define H 5
enum {E=0, P=1};
static const char grid[] = {
    P, P, E, P, P,
    P, P, E, E, P,
    E, E, P, E, P,
    P, P, E, P, P,
    P, E, E, E, P,
};
static const signed char moves[] = {
    -2,-1, -2,+1, +2,-1, +2,+1, -1,-2, -1,+2, +1,-2, +1,+2
};

static int solve(int *p, int n, int phase, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        if (phase & 1) {
            for (int i = 0; i < 8; i++) {
                int xx = x + moves[i*2 + 0];
                int yy = y + moves[i*2 + 1];
                if (xx>=0 && xx<W && yy>=0 && yy<H) {
                    int t = yy*W + xx;
                    if (grid[t] == P) {
                        p[n+1] = t;
                        bestn = solve(p, n+1, (phase+1)&1, bestn);
                    }
                }
            }
        } else {
            for (int i = 0; i < 4; i++) {
                for (int v = 1; ; v++) {
                    int dx, dy;
                    switch (i) {
                        case 0: dx = -v; dy = +0; break;
                        case 1: dx = +v; dy = +0; break;
                        case 2: dx = +0; dy = -v; break;
                        case 3: dx = +0; dy = +v; break;
                    }
                    int xx = x + dx;
                    int yy = y + dy;
                    if (xx<0 || xx>=W || yy<0 || yy>=H) break;
                    int t = yy*W + xx;
                    if (grid[t] == P) {
                        p[n+1] = t;
                        bestn = solve(p, n+1, (phase+1)&1, bestn);
                        break;
                    }
                }
            }
        }
    }
    return bestn;
}

int main()
{
    int path[12] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
    return 0;
}
