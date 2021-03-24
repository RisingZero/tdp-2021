/* LAB1 ES4 TDP */

#include <stdio.h>
#define PI 3.14

int main(int argc, char const *argv[])
{
    char c, option;
    int next = 1;
    float area;
    while (next == 1) {
        printf("Cosa vuoi calcolare? \nQ per area del quadrato\nC per area del cerchio\nX per chiudere\nInserire: ");
        scanf("%c", &c);

        if (c == 'Q'){
            getchar();
            printf("CALCOLO AREA DEL QUADRATO\n");
            printf("Come vuoi calcolare?\nD usando la diagonale\nL usando il lato\nInserire: ");
            scanf("%c", &option);
            getchar();

            if (option == 'D') {
                float diagonale;
                printf("Inserire valore diagonale: ");
                scanf("%f", &diagonale);

                area = diagonale * diagonale / 2;
            } else if (option == 'L') {
                float lato;
                printf("Inserire valore lato: ");
                scanf("%f", &lato);

                area = lato * lato;
            } else {
                printf("Valore non valido!\n");
            }

            getchar();
            printf("Area: %.2f\n", area);

        } else if (c == 'C') {
            getchar();
            printf("CALCOLO AREA DEL CERCHIO\n");
            printf("Come vuoi calcolare?\nD usando il diametro\nR usando il raggio\nInserire: ");
            scanf("%c", &option);
            getchar();

            if (option == 'D') {
                float diametro;
                printf("Inserire valore diametro: ");
                scanf("%f", &diametro);

                area = PI * diametro * diametro / 4;
            } else if (option == 'R') {
                float raggio;
                printf("Inserire valore raggio: ");
                scanf("%f", &raggio);

                area = PI * raggio * raggio;
            } else {
                printf("Valore non valido!\n");
            }

            getchar();
            printf("Area: %.2f\n", area);
        } else if (c == 'X') {
            getchar();
            next = 0;
        } else {
            printf("ERRORE: valore non valido!\n");
        }

    }
    return 0;
}
