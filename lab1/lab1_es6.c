/*  LAB1 ES6 TDP ANDREA RAINERI RAINERI S280848 */

#include <stdio.h>

int main(void)
{
    FILE *fin, *fout;
    char operation;
    float op1, op2, result;

    // Apertura file di input
    if ((fin = fopen("Operations.txt", "r")) == NULL) {
        printf("ERRORE APERTURA FILE");
        return 1;
    }
    
    // Apertura file di output
    if ((fout = fopen("out.txt", "w")) == NULL) {
        printf("ERRORE APERTURA FILE");
        return 2;
    }

    while (!feof(fin)) { //Check for EOF
        fscanf(fin, "%c%f%f", &operation, &op1, &op2); // Lettura riga
        if (!feof(fin)) {
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
                        fprintf(fin, "%c ERRORE: non e' possibile dividere per 0!\n", operation);
                    else
                        fprintf(fout, "%c %.2f\n", operation, op1 / op2);
                    break;
                default:
                    fprintf(fin, "%c Operazione non riconosciuta\n", operation);
            }
            getc(fin); // Lettura carattere new line
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
