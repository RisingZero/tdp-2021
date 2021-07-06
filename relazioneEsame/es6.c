#include <stdio.h>
#define DIM 100

int areaIntersection(FILE * fp) {
    int x1, y1, x2, y2, i, j, area = 0;
    int M[DIM][DIM] = {0};

    // Lettura file
    while (fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2) == 4) {
        for (j = x1; j < x2; j++) {
            for (i = DIM - y1 - 1; i > DIM - y2 - 1; i--) {
                // Verifica intersezione
                if (M[i][j] == 1)
                    area++;
                else
                    M[i][j] = 1;
            }
        }
    }
    return area;
}

int main(void) {
    FILE *fp;
    int area;
    fp = fopen("area.txt", "r");

    area = areaIntersection(fp);
    printf("%d\n", area);
    return 0;
}