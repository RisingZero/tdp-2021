// LAB 5 ES 1 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#define MAX_SQUADRE 20
#define MAX_GIORNATE 20
#define MAXLEN_FILENAME 20

void leggiPunteggi(FILE *fin, int punteggi[MAX_SQUADRE][MAX_GIORNATE], int dim_matrix[]);
void analisiPunteggi(int punteggi[MAX_SQUADRE][MAX_GIORNATE], int dim_matrix[]);

int main(void) {
    FILE *fin;
    int punteggi[MAX_SQUADRE][MAX_GIORNATE] = {0}, dim_matrix[2];
    char filename[MAXLEN_FILENAME + 1];

    printf("Inserire nome del file da cui leggere i punteggi: ");
    scanf("%s", filename);

    if ((fin = fopen(filename, "r")) == NULL) {
        printf("Errore apertura del file di input");
        return 1;
    }

    // Lettura matrice da file
    leggiPunteggi(fin, punteggi, dim_matrix);

    // Stampa top-team per giornata
    analisiPunteggi(punteggi, dim_matrix);

    return 0;
}

void leggiPunteggi(FILE *fin, int punteggi[MAX_SQUADRE][MAX_GIORNATE], int dim_matrix[]) {

    /* 
        Lettura numero squadre e numero giornate da prima riga
        dim_matrix: salva il numero di squadre e il numero di giorni, reali dimensioni della matrice
     */

    int i, j;
    fscanf(fin, "%d %d", dim_matrix[0], dim_matrix[1]);

    /* 
        Lettura punteggi
        Ogni riga è una squadra, ogni colonna è una giornata
     */

    for (i = 0; i < dim_matrix[0]; i++) {
        for (j = 0; j < dim_matrix[1]; j++) {
            fscanf(fin, "%d", punteggi[i][j]);
        }
    }

    printf("Lettura completata correttamente\n");
}

void analisiPunteggi(int punteggi[MAX_SQUADRE][MAX_GIORNATE], int dim_matrix[]) {

    /* 
        Si salvano punteggi parziali del campionato in un vettore, aggiornato per ogni giornata.
        Si trova per ogni giornata il parziale massimo e si stampa l'indice del relativa squadra.
     */

    int i, j, max = 0, bestIdx;
    int parziali[MAX_SQUADRE] = {0};

    for (j = 0; j < dim_matrix[1]; j++) {
        for (i = 0; i < dim_matrix[0]; i++) {
            parziali[i] += punteggi[i][j];

            if (parziali[i] > max) {
                max = parziali[i];
                bestIdx = i;
            }
        }

        printf("Giornata %d: Squadra %d in cima alla classifica\n", j+1, bestIdx);
    }
}