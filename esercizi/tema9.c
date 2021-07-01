#include <stdio.h>
#define MAXN 50
#define MAXM 50

void displRanking(int C[MAXN][MAXM], int n, int m);

int main(void) {
    int teams[MAXM][MAXM] = {{3,1,0},{0,1,1},{1,1,1},{1,1,3}};
    int n = 4, m = 3;

    displRanking(teams, n, m);
    return 0;
}

void displRanking(int C[MAXN][MAXM], int n, int m) {
    int sq[MAXN] = {0}, day, i, bestTeam = 0;

    for (day = 0; day < m; day++) {
        for (i = 0; i < n; i++) {
            sq[i] += C[i][day];
            if (sq[i] > sq[bestTeam])
                bestTeam = i;
        }
        printf("Giornata %d, Squadra capolista %d\n", day+1, bestTeam+1);
    }
}