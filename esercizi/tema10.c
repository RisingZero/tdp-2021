#include <stdio.h>
#define MAXR 50
#define MAXC 50

int buildMatrix(int V[], int N, int M[MAXR][MAXC], int nr, int nc);

int main(void) {
    int nr = 3, nc = 5, N = 14, V[] = {1,2,17,2,3,1,8,4,6,1,7,3,5,2};
    int M[MAXR][MAXC] = {0};
    int res;

    res = buildMatrix(V, N, M, nr, nc);
    printf("%d\n", res);
    
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int buildMatrix(int V[], int N, int M[MAXR][MAXC], int nr, int nc) {
    int i, j, cnt = 0, row, col;

    for (i = 0; i < N; i += 2) {
        for (j = 0; j < V[i+1]; j++) {
            row = cnt/nc;
            col = cnt%nc;
            M[row][col] = V[i];
            cnt++;
        }
    }

    if (cnt == (nr*nc))
        return 1;
    else
        return 0;
}