#include <stdio.h>

#define W 5
#define H 5
#define T 21

static const struct {
    enum { M, A } op;
    int value;
} grid[] = {
    {M, +0}, {A, +1}, {M, +3}, {A, +2}, {A, -2},
    {A, +1}, {M, +4}, {M, +2}, {A, -2}, {A, -2},
    {M, +2}, {A, +2}, {A, -2}, {A, +2}, {M, +2},
    {A, +2}, {A, -2}, {M, +2}, {M, +4}, {A, +1},
    {A, +0}, {A, +2}, {M, +3}, {A, +3}, {A, +1},
};
static const int moves[] = {
    -1, +0, +1, +0, +0, -1, +0, +1
};

static int
solve(int *p, int n, int v, int bestn)
{
    switch (grid[p[n]].op) {
        case M:
            v *= grid[p[n]].value;
            break;
        case A:
            v += grid[p[n]].value;
            break;
    }

    if (p[n] == H * W - 1 && v == T) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int x = p[n] % W;
        int y = p[n] / W;
        for (int i = 0; i < 4; i++) {
            int xx = x + moves[i * 2 + 0];
            int yy = y + moves[i * 2 + 1];
            if (xx >= 0 && xx < W && yy >= 0 && yy < H) {
                p[n + 1] = xx + yy * W;
                bestn = solve(p, n + 1, v, bestn);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[24] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path));
    return 0;
}
