#include <stdio.h>

#define H 8
#define W 8
static const char grid[] = {
    0, 1, 1, 0, 1, 0, 0, 1,
    1, 1, 1, 0, 1, 1, 1, 1,
    0, 0, 1, 0, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 1,
    1, 1, 1, 1, 0, 0, 1, 1,
    1, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 0, 1, 1, 0, 1, 1
};
static const signed char moves[] = {
    +1,-2, +2,-1, +2,+1, +1,+2, -1,+2, -2,+1, -2,-1, -1,-2
};

static int solve(int *p, int n, int bestn, int *visited)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i < n; i++) {
            printf("%d%c", 1 + p[i], i < n - 1 ? ' ' : '\n');
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 8; i++) {
            int tx = x + moves[i*2 + 0];
            int ty = y + moves[i*2 + 1];
            int t  = ty*W + tx;
            if (tx>=0 && tx<W && ty>=0 && ty<H && grid[t] && !visited[t]) {
                p[n+1] = t;
                visited[t] = 1;
                bestn = solve(p, n+1, bestn, visited);
                visited[t] = 0;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[23] = {0};
    int visited[W*H] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path), visited);
    return 0;
}
