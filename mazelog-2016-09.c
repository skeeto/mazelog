#include <stdio.h>

static char game[8][8] = {
    "nbrnnnnr",
    "rbnn n n",
    "bnnnrbb ",
    "rnrkknnb",
    "rbrkk n ",
    "bnn r  n",
    "nnnnn bn",
    "n  nnnnn",
};

static const char knight[] = {
    1, -2, 2, -1, 2, 1, 1, 2, -1, 2, -2, 1, -2, -1, -1, 2
};

static const char bishop[] = {
    1, -1, 1, 1, -1, 1, -1, -1
};

static const char rook[] = {
    0, -1, 1, 0, 0, 1, -1, 0
};

static const char king[] = {
    0, -1, 1, -1, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1
};

static struct {
    char x;
    char y;
} path[32];
unsigned best = sizeof(path) / sizeof(path[0]);

static void
output(unsigned n)
{
    if (n < best) {
        best = n;
        for (unsigned i = 0; i < n; i++)
            printf("%d%c", 8 * path[i].y + path[i].x + 1, " \n"[i == n - 1]);
    }
}

#define VALID(x, y) ((x) >= 0 && (x) < 8 && (y) >= 0 && (y) < 8)

static void
solve(unsigned n)
{
    if (n == best)
        return;
    int x = path[n - 1].x;
    int y = path[n - 1].y;
    if (x == 7 && y == 7) {
        output(n);
        return;
    }
    char c = game[y][x];
    game[y][x] = '#';
    switch (c) {
        case 'k':
        case 'n': {
            const char *base = c == 'n' ? knight : king;
            for (int i = 0; i < 8; i++) {
                int tx = x + base[i * 2 + 0];
                int ty = y + base[i * 2 + 1];
                if (VALID(tx, ty)) {
                    path[n].x = (char)tx;
                    path[n].y = (char)ty;
                    solve(n + 1);
                }
            }
        } break;
        case 'b':
        case 'r': {
            const char *base = c == 'r' ? rook : bishop;
            for (int i = 0; i < 4; i++) {
                int tx = x;
                int ty = y;
                do {
                    tx += base[i * 2 + 0];
                    ty += base[i * 2 + 1];
                } while (VALID(tx, ty) && game[ty][tx] == ' ');
                if (VALID(tx, ty)) {
                    path[n].x = (char)tx;
                    path[n].y = (char)ty;
                    solve(n + 1);
                }
            }
        } break;
    }
    game[y][x] = c;
}

int
main(void)
{
    solve(1);
    return 0;
}
