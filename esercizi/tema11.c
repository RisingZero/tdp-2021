#include <stdio.h>
#define DIM 10

int areaTot(FILE *fp);

int main(void) {
    FILE *fp;
    int area;
    fp = fopen("area.txt", "r");

    area = areaTot(fp);
    printf("%d\n", area);
    return 0;
}

int areaTot(FILE *fp) {
    int plane[DIM][DIM] = {0};
    int x1, y1, x2, y2, i, j, area = 0;

    while(!feof(fp)) {
        fscanf(fp, "%d %d", &x1, &y1);
        fscanf(fp, "%d %d", &x2, &y2);
        
        for (i = DIM - y1 - 1; i > DIM - y2 - 1; i--) {
            for (j = x1; j < x2; j++) {
                if (plane[i][j] != 1) {
                    plane[i][j] = 1;
                    area++;
                }
            }
        }
    }

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            printf("%d ", plane[i][j]);
        }
        printf("\n");
    }

    return area;
}