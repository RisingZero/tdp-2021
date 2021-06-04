// LAB 8 ES 1 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#define NR 50
#define NC 50
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
    int row, col;
    int altezza; int larghezza; int area;
} Region;


void leggiMatrice(int mat[][NC], int maxR, int *nrp, int *ncp);
int riconosciRegione(int mat[][NC], int nr, int nc, int row, int col, int *b, int *h);
void assignRegion(Region *r, int b, int h, int row, int col);
void printRegion(Region r, char type[]);

int main(int argc, char const *argv[])
{
    int M[NR][NC] = {0}, nr, nc, i, j, b, h;
    Region maxB = {0}, maxH = {0}, maxA = {0};

    leggiMatrice(M, NR, &nr, &nc);

    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if (M[i][j] == black && riconosciRegione(M, nr, nc, i, j, &b, &h)) {
                if (b > maxB.larghezza)
                    assignRegion(&maxB, b, h, i, j);
                if (h > maxH.altezza)
                    assignRegion(&maxH, b, h, i, j);
                if ((b*h) > maxA.area)
                    assignRegion(&maxA, b, h, i, j);
            }
        }
    }

    printRegion(maxH, "altezza");
    printRegion(maxB, "larghezza");
    printRegion(maxA, "area");
    
    return 0;
}

void leggiMatrice(int mat[][NC], int maxR, int *nrp, int *ncp) {

    FILE *fin;
    int i, j;

    if ((fin = fopen(FILENAME, "r")) == NULL) {
        printf("ERRORE lettura file input");
    }

    fscanf(fin, "%d%d", nrp, ncp);
    for (i = 0; i < *nrp && i < maxR; i++) {
        for (j = 0; j < *ncp; j++) {
            fscanf(fin, "%d", &mat[i][j]);
        }
    }

    fclose(fin);
}

int riconosciRegione(int mat[][NC], int nr, int nc, int row, int col, int *b, int *h) {
    
    int p, dim, top, left;

    top = row == 0 || mat[row-1][col] == white;
    left = col == 0 || mat[row][col-1] == white;

    *b = *h = 0;

    if (top && left) {
        // Check base dimension
        for (p = col, dim = 0; p < nc; p++) {
            if (mat[row][p] == black) {
                (*b)++;
            }
            else {                
                break;
            }
        }

        // Check heigth dimension
        for (p = row, dim = 0; p < nr; p++) {
            if (mat[p][col] == black){
                (*h)++;
            } else {
                break;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

void assignRegion(Region *r, int b, int h, int row, int col) {
    r->larghezza = b;
    r->altezza = h;
    r->area = b*h;
    r->row = row;
    r->col = col;
}

void printRegion(Region r, char type[]) {
    printf("Max %s: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n", type, r.row, r.col, r.altezza, r.larghezza, r.area);
}