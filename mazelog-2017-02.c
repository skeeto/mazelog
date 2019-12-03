#include <stdio.h>

#define W 8
#define H 8
enum direction {UU, UR, RR, DR, DD, DL, LL, UL};
static const signed char grid[] = {
    DD, DR, RR, DR, DD, DR, LL, DL,
    UR, DD, DR, DR, DR, RR, UR, DD,
    RR, UR, UU, UR, LL, DL, RR, LL,
    UR, UR, DL, UL, DR, LL, UU, UL,
    UU, DR, DD, UR, LL, UL, DR, UL,
    UR, RR, UL, DR, UR, UU, DL, DL,
    DR, UL, RR, UR, UU, UL, UU, UL,
    UR, LL, UR, UR, UL, UL, RR, -1,
};
static const signed char moves[] = {
    +0, -1,  +1, -1,  +1, +0,  +1, +1,
    +0, +1,  -1, +1,  -1, +0,  -1, -1,
};

#define VALID(x, y)   ((x) >= 0 && (x) < W && (y) >= 0 && (y) < H)
#define VISIT(v, n)   ((v) | (1ULL << (n)))
#define VISITED(v, n) ((v) & (1ULL << (n)))

static int
solve(int *p, int n, int m, int bestn, unsigned long long visit)
{
    if (p[n] == H * W - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int sx = p[n] % W;
        int sy = p[n] / W;
        int dx = moves[grid[p[n]] * 2 + 0];
        int dy = moves[grid[p[n]] * 2 + 1];
        for (int x = sx + dx, y = sy + dy; VALID(x, y); x += dx, y += dy) {
            int next = x + y * W;
            if (!VISITED(visit, next)) {
                p[n + 1] = next;
                visit = VISIT(visit, next);
                bestn = solve(p, n + 1, m, bestn, visit);
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[24] = {0};
    solve(path, 0, 0, sizeof(path) / sizeof(*path), VISIT(0, 1));
    return 0;
}
