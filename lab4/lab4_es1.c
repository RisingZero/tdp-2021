// LAB 4 ES 1 s280848 RAINERI ANDREA ANGELO

#include <stdio.h>
#define MAXLEN 30

void sottoSequenze(int V[], int N);

int main(void)
{
    int numeri[MAXLEN] = {0}, i, N;

    printf("Indicare la dimensione del vettore che si vuole inserire: ");
    scanf("%d", &N);

    // Input numeri da utente
    for (i=0; i<N; i++) {
        printf("Inserire elemento %d del vettore di interi: ", i+1);
        scanf("%d", &numeri[i]);
    }

    // Chiamata funzione
    sottoSequenze(numeri, N);
    return 0;
}

void sottoSequenze(int V[], int N) {
    // Funzione che visualizza tutti i sottovettori
    // di dimensione massima contenuti nel vettor V

    int i, j, first, start = -1, dimMax = 0;
    int sottovettori[MAXLEN] = {0};

    // Scansione vettore in cerca di tutti i sottovettori
    // sottovettori[i] = posizione finale sottovettore con posizione iniziale = i
    for (i = 0; i < N; i++) {
        if (V[i] != 0 && start == -1)
            start = i;

        if ((V[i] == 0 || i == N-1) && start != -1) {
            if ((i - start) > dimMax)
                dimMax = i - start;
            sottovettori[start] = (i == N-1) ? i : i-1;
            start = -1;
        }
    }

    // Stampa a video dei sottovettori
    for (i = 0; i<N; i++) {
        if ((sottovettori[i] - i + 1) == dimMax){
            printf("[");
            for (j = i, first = 0; j<=sottovettori[i]; j++, first++) {
                if (first > 0)
                    printf(" ");
                printf("%d", V[j]);
            }
            printf("]\n");
        }
    }
}