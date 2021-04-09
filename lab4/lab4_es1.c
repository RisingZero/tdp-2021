// LAB 4 ES 1 s280848 RAINERI ANDREA ANGELO

#include <stdio.h>
#define MAXLEN 30

void sottoSequenze(int V[], int N);

int main(void)
{
    int numeri[MAXLEN] = {0}, i;

    // Input numeri da utente
    for (i=0; i<MAXLEN; i++) {
        printf("Inserire elemento %d del vettore di interi: ", i);
        while (scanf("%d", &numeri[i]) != 1) {      // Errore input non intero
            printf("ERRORE: inserire un numero intero");
        }
    }

    // Chiamata funzione
    sottoSequenze(numeri, MAXLEN);
    return 0;
}

void sottoSequenze(int V[], int N) {
    // Funzione che visualizza tutti i sottovettori
    // di dimensione massima contenuti nel vettor V

    int i, j, first, start = 0, end = 0, dimMax = 0;
    int sottovettori[MAXLEN] = {0};

    // Scansione vettore in cerca di tutti i sottovettori
    for (i = 0; i < N; i++) {
        if (V[i] != 0 && start == 0)
            start = i;

        if (V[i] == 0) {
            if ((i - start) > dimMax)
                dimMax = i - start;
            sottovettori[start] = i;
            start = 0;
        }
    }

    for (i = 0; i<MAXLEN; i++) {
        if (i - sottovettori[i] == dimMax){
            printf("[");
            for (j = sottovettori[i], first = 0; j<i; j++, first++) {
                if (first > 0)
                    pritnf(" ");
                printf("%d");
            }
            printf("]");
        }
    }
}
