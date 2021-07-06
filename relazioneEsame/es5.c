#include <stdio.h>
#define DIM 50

float matrMaxDiag(float M[DIM][DIM], int n) {
    int i, j;
    float maxAvg, avgs[DIM] = {0};

    // Somma di tutti gli elementi sulle diagonali e memorizzazione nel vettore avgs
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            avgs[i-j+n-1] += M[i][j];
        }
    }

    // Calcolo delle medie
    for (i = 0; i < n*2 - 1; i++) {
        if ((i+1) <= n)
            avgs[i] /= i+1;
        else
            avgs[i] /= (n - (i+1)%n);
    }
    
    // Identificazione massimo
    maxAvg = avgs[0];
    for (i = 1; i < n*2 - 1; i++) {
        if (maxAvg < avgs[i])
            maxAvg = avgs[i];
        }

    return maxAvg;
}

int main(void) {

    float M[DIM][DIM] = {{1.0,2.0,3.0,4.0,5.0},
                         {2.0,2.0,2.0,2.0,-2.0},
                         {1.1,2.2,3.3,-4.4,5.5},
                         {2.2,2.2,-3.2,4.2,4.2},
                         {1.8,-2.3,3.1,4.9,5.0}};
    float maxAvg = matrMaxDiag(M, 5);
    printf("Max diag average: %.1f", maxAvg);
    return 0;
}