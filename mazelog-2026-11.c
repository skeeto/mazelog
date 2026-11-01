#include <stdio.h>

#define W 5
#define H 5
enum {D=0, HEART=1, CLUB=2, SPADE=3};
static const unsigned char grid[W*H] = {
    D, HEART, CLUB, D, D,
    HEART, SPADE, HEART, D, HEART,
    D, D, SPADE, CLUB, D,
    HEART, SPADE, HEART, HEART, D,
    D, D, D, D, D
};

static char seen[W*H*(W*H+1)];

static int solve(int *p, int n, int bestn)
{
    int cur = p[n];
    int prev = (n > 0) ? p[n-1] : -1;
    if (cur == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i == n]);
        }
        return n;
    }
    if (n >= bestn - 1) return bestn;

    int cr = cur / W;
    int cc = cur % W;

    /* try all cells in same row */
    for (int c = 0; c < W; c++) {
        if (c == cc) continue;
        int t = cr * W + c;
        if (grid[t] == grid[cur]) continue;
        if (n > 0 && grid[t] == grid[prev]) continue;
        if (n > 0) {
            int pr = prev / W;
            int pc = prev % W;
            if (cr == pr) {
                int dir = (cc > pc) ? 1 : -1;
                int ndir = (c > cc) ? 1 : -1;
                if (ndir == -dir) continue;
            }
        }
        int idx = t * (W*H + 1) + (cur + 1);
        if (seen[idx]) continue;
        seen[idx] = 1;
        p[n+1] = t;
        bestn = solve(p, n+1, bestn);
        seen[idx] = 0;
        if (bestn == n+1) return bestn;
    }
    /* try all cells in same column */
    for (int r = 0; r < H; r++) {
        if (r == cr) continue;
        int t = r * W + cc;
        if (grid[t] == grid[cur]) continue;
        if (n > 0 && grid[t] == grid[prev]) continue;
        if (n > 0) {
            int pr = prev / W;
            int pc = prev % W;
            if (cc == pc) {
                int dir = (cr > pr) ? 1 : -1;
                int ndir = (r > cr) ? 1 : -1;
                if (ndir == -dir) continue;
            }
        }
        int idx = t * (W*H + 1) + (cur + 1);
        if (seen[idx]) continue;
        seen[idx] = 1;
        p[n+1] = t;
        bestn = solve(p, n+1, bestn);
        seen[idx] = 0;
        if (bestn == n+1) return bestn;
    }
    return bestn;
}

int main(void)
{
    int path[256];
    path[0] = 0;
    seen[0 * (W*H + 1) + 0] = 1;
    int best = sizeof(path)/sizeof(*path);
    best = solve(path, 0, best);
    return 0;
}
