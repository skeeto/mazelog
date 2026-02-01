#include <stdio.h>

#define W 11
#define H 11

static const char grid[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 5, 2, 4, 1, 2, 3, 2, 7, 2, 0,
    0, 1, 6, 2, 7, 1, 7, 5, 3, 2, 0,
    0, 4, 4, 4, 1, 4, 2, 2, 1, 2, 0,
    0, 1, 5, 5, 2, 1, 3, 1, 1, 3, 0,
    0, 2, 1, 6, 3, 1, 3, 1, 1, 2, 0,
    0, 3, 7, 5, 2, 2, 3, 2, 3, 2, 0,
    0, 4, 4, 4, 2, 1, 5, 5, 2, 4, 0,
    0, 3, 6, 4, 1, 6, 1, 4, 7, 4, 0,
    0, 4, 4, 5, 2, 4, 2, 2, 4, 7, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
static const signed char moves[] = {
    +0, -1, +0, +1, -1, +0, +1, +0,
};

static int solve(int *p, int n, char *visited, int bestn)
{
    if (!grid[p[n]]) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i==n]);
        }
        bestn = n;
    } else if (n < bestn-1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int v = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            int xx = x + v*moves[i*2 + 0];
            int yy = y + v*moves[i*2 + 1];
            int t  = yy*W + xx;
            if (xx>=0 && xx<W && yy>=0 && yy<H && !visited[t]) {
                visited[t] = 1;
                p[n+1] = t;
                bestn = solve(p, n+1, visited, bestn);
                visited[t] = 0;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[22] = {5*W + 5};
    char visited[W*H] = {0};
    solve(path, 0, visited, sizeof(path)/sizeof(*path));
}
