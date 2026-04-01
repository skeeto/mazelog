#include <stdio.h>

#define W 7
#define H 7

static char grid[] = {
    4, 3, 4, 2, 3, 2, 3,
    2, 4, 5, 3, 0, 2, 4,
    2, 0, 2, 4, 4, 3, 4,
    4, 3, 2, 0, 3, 2, 5,
    3, 2, 4, 3, 1, 0, 4,
    3, 4, 0, 5, 4, 5, 5,
    6, 3, 5, 1, 3, 4, 0,
};
static const int missing[] = {11, 15, 24, 33, 37};
static const signed char moves[] = { -1,+0, +1,+0, +0,-1, +0,+1 };

static int solve(int *p, int n, char *visited, int bestn)
{
    if (p[n] == W*H - 1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int d = grid[p[n]];
        for (int i = 0; i < 4; i++) {
            int xx = x + d*moves[i*2 + 0];
            int yy = y + d*moves[i*2 + 1];
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
    int bestn = 21;
    for (int a = 1; a <= 6; a++) {
        for (int b = 1; b <= 6; b++) {
            for (int c = 1; c <= 6; c++) {
                for (int d = 1; d <= 6; d++) {
                    for (int e = 1; e <= 6; e++) {
                        grid[missing[0]] = a;
                        grid[missing[1]] = b;
                        grid[missing[2]] = c;
                        grid[missing[3]] = d;
                        grid[missing[4]] = e;
                        int path[49] = {0};
                        char visited[W*H] = {1};
                        int n = solve(path, 0, visited, bestn);
                        if (n < bestn) {
                            bestn = n;
                        }
                    }
                }
            }
        }
    }
}
