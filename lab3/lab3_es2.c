// ES 2 LAB 3 RAINERI ANDREA ANGELO s280848

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_LEN 50

int checkExpr(char[]);
enum ERRORS { OK, NUM_ERR, OPERAND_ERR };

int main(int argc, char const *argv[])
{
    FILE *fin;
    char expr[MAX_LEN + 1];
    int esito, counter = 1;

    if ((fin = fopen("expr.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    
    while (fgets(expr, MAX_LEN, fin) != NULL) {
        if ((esito = checkExpr(expr)) == NUM_ERR)
            printf("Errore nella lettura di un numero (espressione %d)\n", counter);
        else if (esito == OPERAND_ERR)
            printf("Errore nella lettura di un operando (espressione %d)\n", counter);
        counter++;
    }
    
    return 0;
}

int checkExpr(char expr[]) {
    int i;
    printf("%s", expr);
    for (i = 0; i < strlen(expr); i++) {
        
    }
}
