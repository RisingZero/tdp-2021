#include <stdio.h>

#define MAXN 50

int sommaCornici(int mat[MAXN][MAXN], int N, int vet[]);

int main(void) {
    int mat[MAXN][MAXN] = {{1,2,3,4,5},{6,7,8,9,0},{1,2,3,4,5},{6,7,8,9,0},{1,1,1,1,1}};
    int vet[MAXN] = {0};
    int N = 5, cornici;

    cornici = sommaCornici(mat, N, vet);
    printf("cornici: %d\n", cornici);
    for (int i = 0; i < N; i++) {
        printf("%d ", vet[i]);
    }
    
    return 0;
}

int sommaCornici(int mat[MAXN][MAXN], int N, int vet[]) {
    int n = N/2 + 1, a, i, j, sum;

    for (a = 0; a <= n; a++) {
        sum = 0;
        for (i = a; i < N - a; i++) {
            for (j = a; j < N - a; j++) {
                if (i == a || (N - i) == (a + 1) || j == a || (N - j) == (a + 1))
                    sum += mat[i][j];
            }
        }
        vet[a] = sum;
    }
    return n;
}