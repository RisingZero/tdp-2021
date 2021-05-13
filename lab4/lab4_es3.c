// LAB 4 ES 3 s280848 RAINERI ANDREA ANGELO

#include <stdio.h>
#define MAX_DIM_MATRIX 20
#define MAX_DIM_FILENAME 20

typedef struct {int nr; int nc;} dim_matrix;

dim_matrix leggiMatrice(FILE* fin, int matrice[][MAX_DIM_MATRIX]);
void trovaSottomatrici(int matrice[][MAX_DIM_MATRIX], dim_matrix dimensions, int dim);
int stampaMatrice(int matrice[][MAX_DIM_MATRIX], int x, int y, int dim);

int main(void) {
    FILE *fin;
    int matrice[MAX_DIM_MATRIX][MAX_DIM_MATRIX];
    int dim, continua = 1;
    dim_matrix dimensions;
    char filename[MAX_DIM_FILENAME];

    printf("Inserire nome file:\n");
    scanf("%s", filename);

    if ((fin = fopen(filename, "r")) == NULL) {
        printf("ERRORE apertura file");
        return 1;
    }

    dimensions = leggiMatrice(fin, matrice);
    fclose(fin);
    
    do {
        printf("Indicare dimensione delle sottomatrici da ricercare: ");
        scanf("%d", &dim);

        if (dim > dimensions.nc || dim > dimensions.nr) {
            printf("ERRORE: dimensione indicata non compatibile con le dimensioni della matrice");
            continua = 0;
        } else if (dim == 0){
            continua = 0;
        } else {
            trovaSottomatrici(matrice, dimensions, dim);
        }
    } while (continua);
    return 0;
}

dim_matrix leggiMatrice(FILE* fin, int matrice[][MAX_DIM_MATRIX]) {
    
    dim_matrix dimensions;
    int i, j;

    // Lettura dimensioni dalla prima riga
    fscanf(fin, "%d %d", &dimensions.nr, &dimensions.nc);
    // Lettura dati matrice
    for (i = 0; i < dimensions.nr; i++) {
        for (j = 0; j < dimensions.nc; j++) {
            fscanf(fin, "%d", &matrice[i][j]);
        }
    }

    return dimensions;
}

void trovaSottomatrici(int matrice[][MAX_DIM_MATRIX], dim_matrix dimensions, int dim) {
    /*
        Trova e stampa tutte le sottomatrici quadrate contenute in 'matrice'
        identificando l'elemento (0,0)
        Stampa la sottomatrice con somma degli elementi massima.
    */
    
    int x, y, sum, maxSum = 0, i, j, row, col;

    printf("Le sottomatrici quadrate di dimensione %d sono: \n", dim);
    for (i = 0; i + dim <= dimensions.nr; i++) {
        for (j = 0; j + dim <= dimensions.nc; j++) {
            sum = stampaMatrice(matrice, j, i, dim);
            printf("\n");

            if (sum > maxSum) {
                y = i; x = j;
                maxSum = sum;
            }
        }
    }

    printf("La sottomatrice con somma degli elementi massima (%d) e' :\n", maxSum);
    stampaMatrice(matrice, x, y, dim);
}

int stampaMatrice(int matrice[][MAX_DIM_MATRIX], int x, int y, int dim) {
    /* 
        Stampa una matrice quadrata di ordine 'dim'
        a partire dalla posizione (x,y)
    */

    int i, j, first, sum = 0;
    for (i = y; i < y + dim; i++) {
        for (j = x, first = 0; j < x + dim; j++, first++) {
            if (first > 0)
                printf(" ");
            printf("%d", matrice[i][j]);
            sum += matrice[i][j];
        }
        printf("\n");
    }

    return sum;
}
