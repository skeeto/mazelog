#include <stdio.h>
#include <stdlib.h>

#define W 8
#define H 8
static const char grid[] = {
    2, 3, 3, 2, 3, 2, 3, 2,
    3, 2, 2, 3, 2, 4, 2, 2,
    3, 2, 3, 2, 3, 2, 3, 2,
    2, 3, 3, 3, 2, 3, 2, 3,
    3, 2, 3, 3, 3, 2, 3, 2,
    2, 1, 2, 3, 2, 4, 2, 2,
    1, 3, 3, 2, 3, 3, 2, 2,
    2, 2, 2, 3, 2, 3, 2, 0
};
static const signed char moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1, -1, -1, -1, +1, +1, -1, +1, +1
};

static int
solve(int *p, int n, char *seen, int bestn)
{
    if (p[n] == H * W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        int j = grid[p[n]];
        seen[p[n]] = 1;
        for (int i = 0; i < 8; i++) {
            int xx = x + j * moves[i * 2 + 0];
            int yy = y + j * moves[i * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                int t = xx + yy * W;
                if (!seen[t]) {
                    p[n + 1] = t;
                    bestn = solve(p, n + 1, seen, bestn);
                }
            }
        }
        seen[p[n]] = 0;
    }
    return bestn;
}

int
main(void)
{
    char seen[W * H] = {0};
    int path[8] = {0};
    solve(path, 0, seen, sizeof(path) / sizeof(*path));
    return 0;
}
