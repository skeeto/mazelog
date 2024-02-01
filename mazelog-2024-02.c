#include <stdio.h>

#define W 5
#define H 4
enum {NN, NE, EE, SE, SS, SW, WW, NW};
enum {B=' ', R='@'};
static const char grid[] = {
    B|SE, B|WW, B|EE, B|WW, R|SW,
    B|SE, B|WW, B|EE, R|SE, B|WW,
    R|SE, B|NE, R|SE, B|SS, R|WW,
    B|NN, B|EE, B|EE, R|NN, B|R

};
static const int moves[] = {0,-1, 1,-1, 1,0, 1,1, 0,1, -1,1, -1,0, -1,-1};
static const char opt[] = " @  @@   @@@    @@@@     @@@@@      ";

static int solve(int *p, int n, int bestn)
{
    if (p[n] == W*H-1) {
        for (int i = 0; i <= n; i++) {
            printf("%d%c", p[i]+1, " \n"[i==n]);
        }
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int a = grid[p[n]] & 0x0f;
        for (int d = 1; ; d++) {
            int xx = x + d*moves[a*2+0];
            int yy = y + d*moves[a*2+1];
            if (xx>=0 && xx<W && yy>=0 && yy<H) {
                int t = yy*W + xx;
                if ((grid[t]&0xf0) & opt[n+1]) {
                    p[n+1] = t;
                    bestn = solve(p, n+1, bestn);
                }
            } else {
                break;
            }
        }
    }
    return bestn;
}

int main(void)
{
    int path[22] = {0};
    solve(path, 0, sizeof(path)/sizeof(*path));
}
