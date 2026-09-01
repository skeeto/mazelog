#include <stdio.h>

#define W 6
#define H 5
enum {E=0, P=1};
static const char grid[] = {
    P, P, P, P, P, P,
    P, E, P, P, P, P,
    P, P, E, E, E, P,
    E, P, P, P, P, E,
    E, P, E, E, P, P,
};
static const signed char moves[] = {
    -1,0, +1,0, 0,-1, 0,+1, -1,-1, -1,+1, +1,-1, +1,+1
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
        int base = (phase < 2) ? 0 : 8;
        for (int i = 0; i < 4; i++) {
            int xx = x + moves[base + i*2 + 0];
            int yy = y + moves[base + i*2 + 1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = yy*W + xx;
                if (grid[t] == P) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, (phase+1)&3, bestn);
                }
            }
        }
    }
    return bestn;
}

int main()
{
    int path[20] = {0};
    solve(path, 0, 0, sizeof(path)/sizeof(*path));
    return 0;
}
