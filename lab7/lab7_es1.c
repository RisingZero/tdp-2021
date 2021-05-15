// LAB 7 ES 1 S280848 RAINERI ANDREA ANGELO

#include <stdio.h>
#define MAX_ROW 50
#define MAX_COL 50
#define CLASS_TYPES 3
#define white 0
#define black 1
#define FILENAME "matrix.txt"

/* 
    Struct containing info about a region:
        - (x,y) of the first pixel (top-left corner)
        - altezza: heigth of the region
        - larghezza: width of the region
        - area: area of the region
            area = larghezza * altezza
 */
typedef struct region_s {
    int x, y;
    int altezza; int larghezza; int area;
} Region;

typedef enum {altezza, larghezza, area} Class;

void readMatrix(int matrix[MAX_ROW][MAX_COL], int *nr, int *nc, FILE *fin);
void findMaxRegions(int matrix[MAX_ROW][MAX_COL], int nr, int nc);
int checkDim(int matrix[MAX_ROW][MAX_COL], int nr, int nc, int i, int j, Class class);

int main(void)
{
    // Variable declaration
    FILE *fin;
    int matrix[MAX_ROW][MAX_COL] = {0};
    int nr, nc;

    // Open file
    if ((fin = fopen(FILENAME, "r")) == NULL) {
        printf("ERRORE in apertura file di input");
        return 1;
    }
    
    // Read matrix from file
    readMatrix(matrix, &nr, &nc, fin);
    fclose(fin);

    // Find max regions of the matrix
    findMaxRegions(matrix, nr, nc);

    return 0;
}

/* 
    FUNCTION: Reads the matrix from the file
    nr: pointer to int, saves the numbers of rows
    nc: pointer to int, saves the numbers of cols
 */
void readMatrix(int matrix[MAX_ROW][MAX_COL], int *nr, int *nc, FILE *fin) {

    int i,j;

    fscanf(fin, "%d%d", nr, nc);
    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++) {
            fscanf(fin, "%d", &matrix[i][j]);
        }
    }
}

int checkDim(int matrix[MAX_ROW][MAX_COL], int nr, int nc, int i, int j, Class class) {
    int p, dim = 0;
    switch (class) {
        case larghezza:
            for (p = j; p < nc; p++) {
                if (matrix[i][p] == black)
                    dim++;
                else
                    break;
            }
            break;
        case altezza:
            for (p = i; p < nr; p++) {
                if (matrix[p][j] == black)
                    dim++;
                else
                    break;
            }
            break;
        default:
            return 0;
    }
    return dim;
}

void findMaxRegions(int matrix[MAX_ROW][MAX_COL], int nr, int nc) {
    Region bestRegions[CLASS_TYPES] = {0}, region = {0};
    int i, j;
    int w, h, a;

    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if (matrix[i][j] == black) {
                // Check if the black pixel is a top-left corner type
                if ((i == 0 && j == 0) ||
                    (i == 0 && (j > 0 && (matrix[i][j-1] == white))) ||
                    (j == 0 && (i > 0 && (matrix[i-1][j] == white))) ||
                    ((i > 0 && (matrix[i-1][j] == white)) && (j > 0 && (matrix[i][j-1] == white)))
                    ) {
                        region.x = i; region.y = j;
                        region.larghezza = checkDim(matrix, nr, nc, i, j, larghezza);
                        region.altezza = checkDim(matrix, nr, nc, i, j, altezza);
                        region.area = region.larghezza * region.altezza;

                        // Update the best selected region for each type
                        if (region.larghezza > bestRegions[larghezza].larghezza)
                            bestRegions[larghezza] = region;
                        if (region.altezza > bestRegions[altezza].altezza)
                            bestRegions[altezza] = region;
                        if (region.area > bestRegions[area].area)
                            bestRegions[area] = region;
                }
            }
        }
    }

    region = bestRegions[altezza];
    printf("Max altezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n",
            region.x, region.y, region.altezza, region.larghezza, region.area);
    region = bestRegions[larghezza];
    printf("Max larghezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n",
            region.x, region.y, region.altezza, region.larghezza, region.area);
    region = bestRegions[area];
    printf("Max area: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n",
            region.x, region.y, region.altezza, region.larghezza, region.area);
}