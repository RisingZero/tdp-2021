/* LAB1 ES5 TDP RAINERI S280848 */

#include <stdio.h>

int main(void)
{
    char operation;
    float op1, op2, result;

    printf("Inserire operazione: ");
    operation = getchar();
    fflush(stdin);  /* Clears input buffer */

    printf("Inserire due valori: ");
    scanf("%f%f", &op1, &op2);

    switch (operation) {
        case '+':
            result = op1 + op2;
            break;

        case '-':
            result = op1 - op2;
            break;
        
        case '*':
            result = op1 * op2;
            break;
        
        case '/':
            if (op2 == 0) { // Check division by zero
                printf("ERRORE: non e' possibile dividere per 0!");
                return 1;
            } else {
                result = op1 / op2;
            }
            break;
        default:
            printf("Operazione non riconosciuta");
    }

    printf("Il risultato è %.2f", result);

    return 0;
}
