#include <stdio.h>

#define W 5
#define H 5

enum { S=0x00, E=0x10, D=0x20, C=0x30, J=0x40 };
static const unsigned char grid[] = {
    S| 1, D|10, S|13, C| 1, E| 3,
    D| 1, E| 7, C|12,    J, C| 6,
    E| 9, S|12, D| 9, E|13, S| 3,
    C|11,    J, E| 5, S|10, D| 7,
    S|11, C| 5, C|10, D| 6, E|12,
};
static const int moves[] = {
    +0, -1, +0, +1, -1, +0, +1, +0,
};

static int solve(int *p, int n, char *visited, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%D%C", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 4; i++) {
            for (int v = 1; ; v++) {
                int xx = x + v*moves[i*2 + 0];
                int yy = y + v*moves[i*2 + 1];
                if (xx<0 || xx>=W || yy<0 || yy>=H) {
                    break;
                }
                int t = yy*W + xx;
                int g = grid[t];
                int c = grid[p[n]]==J ? grid[p[n-1]] : grid[p[n]];
                if ((g==J || !((c^g)&0x30) || !((c^g)&0x0f)) && !visited[t]) {
                    int nc = g==J ? c : g;
                    p[n+1] = yy*W + xx;
                    visited[t] = g != J;
                    bestn = solve(p, n+1, visited, bestn);
                    visited[t] = 0;
                }
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[20] = {0};
    char visited[W*H] = {1};
    solve(path, 0, visited, sizeof(path)/sizeof(*path));
}
