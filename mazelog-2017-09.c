#include <stdio.h>

#define W 5
#define H 4
enum {UU, UR, RR, DR, DD, DL, LL, UL, TL, TR};
static const char grid[] = {
    DR, TL, DL, TR, TL,
    TL, UU, DD, DD, LL,
    TL, UR, DR, UL, UU,
    TR, TL, TR, LL,  0,
};
static const int moves[] = {
    +0, -1, +1, -1, +1, +0, +1, +1, +0, +1, -1, +1, -1, +0, -1, -1
};

int
main(void)
{
    long h = 0;
    long t = 1;
    static char queue[W * H * 16384L];
    static long fromq[W * H * 16384L];
    static char prevd[W * H * 16384L];
    queue[0] = 0;
    fromq[0] = -1;
    prevd[0] = grid[0];

    for (;;) {
        int p = queue[h];
        int d = prevd[h];
        int x = p % W;
        int y = p / W;

        /* Solution found */
        if (p == W * H - 1) {
            int n = 0;
            int path[32];
            while (h >= 0) {
                path[n++] = queue[h] + 1;
                h = fromq[h];
            }
            while (n--)
                printf("%d%c", path[n], "\n "[!!n]);
            break;
        }

        int v = grid[p];
        if (v == TL) {
            v = (d + 6) % 8;
        } else if (v == TR) {
            v = (d + 2) % 8;
        }

        int dx = moves[v * 2 + 0];
        int dy = moves[v * 2 + 1];
        for (int i = 1; ; i++) {
            int cx = x + i * dx;
            int cy = y + i * dy;
            if (cx < 0 || cx >= W || cy < 0 || cy >= H)
                break;
            queue[t] = cy * W + cx;
            fromq[t] = h;
            prevd[t] = v;
            t++;
        }
        h++;
    }
}
