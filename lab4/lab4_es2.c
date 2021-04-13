// LAB 4 ES 2 s280848 RAINERI ANDREA ANGELO

#include <stdio.h>
#include <stdlib.h>
#define maxN 30

typedef struct {
    int pos;
    int dir;
} rotazione_t;

void ruota(int v[maxN], int N, int P, int dir);
void stampaVettore(int v[], int N);

int main(void)
{
    int vettore[maxN] = {0}, N, i, continua = 1;
    rotazione_t rotazione;

    printf("--- ROTAZIONE VETTORE ---\n");
    printf("Inserire dimensione del vettore: ");
    scanf("%d", &N);

    for (i = 0; i < N; i++) {
        printf("Inserire elemento %d del vettore: ", i+1);
        scanf("%d", &vettore[i]);
    }

    do {
        stampaVettore(vettore, N);
        printf("Inserire numero di rotazioni: ");
        scanf("%d", &rotazione.pos);
        
        if (rotazione.pos == 0) {
            continua = 0;
        } else if (!(rotazione.pos < N)) {
            printf("ERRORE: opzione non valida\n");
        } else {        
            printf("Inserire direzione (1 sinistra, -1 destra):  ");
            scanf("%d", &rotazione.dir);
            if (abs(rotazione.dir) != 1)
                printf("ERRORE: opzione non valida\n");
            else
                ruota(vettore, N, rotazione.pos, rotazione.dir);
        }
    } while (continua);

    return 0;
}

void ruota(int v[maxN], int N, int P, int dir) {
    /*
        v[]:    vettore da ruotare, condiviso con la funzione chiamante
        N:      numero di elementi del vettore
        P:      numero di posizioni di rotazione
        dir:    direzione di rotazione {1: sinistra, -1: destra}
    */
    
    int temp, i, iter;

    for (iter = 0; iter < P; iter++) {
        if (dir == 1) {
            for (i = 0; i < N-1; i++) {
                v[i] += v[i+1];
                v[i+1] = v[i] - v[i+1];
                v[i] -= v[i+1];
            }
        } else {
            for (i = N - 2; i >= 0; i--) {
                v[i] += v[i+1];
                v[i+1] = v[i] - v[i+1];
                v[i] -= v[i+1];
            }
        }
    }
}

void stampaVettore(int v[], int N) {
    
    int i, first;

    printf("[");
    for (i = 0, first = 0; i < N; i++, first++) {
        if (first > 0)
            printf(" ");
        printf("%d", v[i]);
    }
    printf("]\n");
}