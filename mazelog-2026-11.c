#include <stdio.h>

#define W 5
#define H 5
enum {D, HR, C, S};
static const char grid[] = {
    D, HR, C, D, D,
    HR, S, HR, D, HR,
    D, D, S, C, D,
    HR, S, HR, HR, D,
    D, D, D, D, D,
};
static const signed char moves[] = {
    -1,+0, +1,+0, +0,-1, +0,+1
};

/* Jumps run any length, and cells may be revisited, so a state is the last two
   cells: they hold the two symbols to avoid, and the direction not to repeat. */
static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]];
        int b = (n < 1) ? -1 : grid[p[n-1]];
        int ux = 0;
        int uy = 0;
        if (n >= 1) {
            int px = p[n-1] % W;
            int py = p[n-1] / W;
            ux = (x>px) - (x<px);
            uy = (y>py) - (y<py);
        }
        for (int i = 0; i < 4; i++) {
            int dx = moves[i*2 + 0];
            int dy = moves[i*2 + 1];
            if (dx == -ux && dy == -uy) continue;
            for (int v = 1; ; v++) {
                int xx = x + v*dx;
                int yy = y + v*dy;
                if (xx<0 || xx>=W || yy<0 || yy>=H) break;
                int t = yy*W + xx;
                if (grid[t]!=a && grid[t]!=b) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, bestn);
                }
            }
        }
    }
    return bestn;
}

int main()
{
    int path[26] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
    return 0;
}
