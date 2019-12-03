#include <stdio.h>

#define S 6
enum shape {SC=0x00, ST=0x01, SX=0x02, SP=0x03, SH=0x04, SV=0x05, SS=0x06};
enum color {CB=0x10, CO=0x20, CP=0x30, CG=0x40, CR=0x50, CY=0x60};
static const unsigned char grid[] = {
    SC|CB, ST|CO, SX|CP, SX|CG, SC|CR, ST|CG,
    SV|CR, ST|CR, ST|CB, SX|CB, SC|CY, SX|CO,
    SC|CO, SH|CG, SP|CP, SH|CO, SC|CP, SP|CR,
    ST|CO, SH|CB, SV|CB, SS|CO, SS|CR, SH|CR,
    ST|CR, SC|CG, SS|CG, SS|CR, SX|CP, SC|CO,    
    SV|CY, SP|CO, SV|CG, SP|CP, SX|CY, SC|CP,
};
static const signed char moves[] = {
    +0, -1, +1, +0, +0, +1, -1, +0,
};

static int
solve(int *p, int n, int bestn)
{
    if (p[n] == S * S - 1) {
        for (int i = 0; i <= n; i++)
            printf("%d%c", p[i] + 1, " \n"[i == n]);
        bestn = n;
    } else if (n < bestn - 1) {
        int s = (n % 2) * 4;
        int x = p[n] % S;
        int y = p[n] / S;
        unsigned v = (grid[p[n]] >> s) & 0xf;
        for (int d = 0; d < 4; d++) {
            for (int r = 1; r < S; r++) {
                int cx = x + r * moves[d * 2 + 0];
                int cy = y + r * moves[d * 2 + 1];
                if (cx < 0 || cx >= S || cy < 0 || cy >= S) 
                    break;
                int cp = cy * S + cx;
                unsigned cv = (grid[cp] >> s) & 0x0f;
                if (v == cv) {
                    p[n + 1] = cp;
                    bestn = solve(p, n + 1, bestn);
                }
            }
        }
    }
    return bestn;
}

int
main(void)
{
    int path[24] = {0};
    solve(path, 0, sizeof(path) / sizeof(*path));
    return 0;
}
