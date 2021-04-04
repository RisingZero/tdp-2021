/*  LAB1 ES6 TDP ANDREA RAINERI RAINERI S280848 */

#include <stdio.h>

int main(void)
{
    FILE *fin, *fout;
    char operation;
    float op1, op2, result;

    // Apertura file di input
    if ((fin = fopen("Operations.txt", "r")) == NULL) {
        printf("ERRORE APERTURA FILE INPUT");
        return 1;
    }
    
    // Apertura file di output
    if ((fout = fopen("out.txt", "w")) == NULL) {
        printf("ERRORE APERTURA FILE OUTPUT");
        return 2;
    }

    while (!feof(fin)) { //Check for EOF
        if (fscanf(fin, "%c %f %f\n", &operation, &op1, &op2) == 3) { // Lettura riga
            switch (operation) {
                case '+':
                    fprintf(fout, "%c %.2f\n", operation, op1 + op2);
                    break;

                case '-':
                    fprintf(fout, "%c %.2f\n", operation, op1 - op2);
                    break;
                
                case '*':
                    fprintf(fout, "%c %.2f\n", operation, op1 * op2);
                    break;
                
                case '/':
                    if (op2 == 0)
                        fprintf(fout, "%c ERRORE: non e' possibile dividere per 0!\n", operation);
                    else
                        fprintf(fout, "%c %.2f\n", operation, op1 / op2);
                    break;
                default:
                    fprintf(fin, "%c Operazione non riconosciuta\n", operation);
            }
        } else {
            fprintf(fout,"ERRORE: riga input non formattata correttamente!\n");
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
