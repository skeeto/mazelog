#include <stdio.h>
#include <stdlib.h>

#define W 5
#define H 5
static const signed char grid[] = {
     +0, -24, +36,  +1,  +9,
    +27,  -5, -11, -11, +32,
     +1,  +9,  -4, -21, -20,
     -9,  -1, -20,  +9, +16,
     -7, +24, -27, +12, +15
};
static const int moves[] = {
    +0, -1, +0, +1, +1, +0, -1, +0
};

static int
isqrt(int v)
{
    if (v == 0) {
        return 0;
    } else if (v == 1) {
        return 1;
    } else if (v < 0) {
        return -1;
    } else {
        int g = v / 2;
        while (g * g != v) {
            int n = (g + v / g) / 2;
            if (abs(n - g) <= 1)
                return n * n == v ? n : -1;
            g = n;
        }
        return g;
    }
}

static int
solve(int *p, int n, int bestn, int sum)
{
    if (p[n] == W * H - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", grid[p[i]], " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int v = 0; v < 4; v++) {
            for (int d = 1; ; d++) {
                int tx = x + d * moves[v * 2 + 0];
                int ty = y + d * moves[v * 2 + 1];
                if (tx >= 0 && tx < W && ty >= 0 && ty < H) {
                    int i = ty * W + tx;
                    int s = grid[i];
                    if (isqrt(sum + s) != -1) {
                        p[n + 1] = i;
                        bestn = solve(p, n + 1, bestn, sum + s);
                    }
                } else {
                    break;
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[13] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path), 0);
}
