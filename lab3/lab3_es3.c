// ES 3 LAB 3 RAINERI ANDREA ANGELO s280848

#include <stdio.h>
#define INPUT "numeri.txt"

int isResult(int,int,int);

int main(int argc, char const *argv[])
{
    FILE *fin;
    int this, prev1, prev2, max, min, dropped = 0, i = 1;

    if ((fin = fopen(INPUT, "r")) == NULL) {        //
        printf("Errore in apertura file");          // Checks correct opening of the file
        return 1;                                   //
    }

    while (!feof(fin)) {
        if (i == 1)                                 //
            fscanf(fin, "%d", &prev2);              // Initialization step
        else if (i == 2) {                          // Read prev2 and prev1 from file, if possible
            fscanf(fin, "%d", &prev1);              //
            max = (prev1 > prev2) ? prev1 : prev2;  // Max and min initialization
            min = (prev1 < prev2) ? prev1 : prev2;  //
        } else {
            fscanf(fin, "%d", &this);               // Read 'this' number from file
            if (isResult(prev2, prev1, this)){      // Checks if 'this' is valid
                max = (this > max) ? this : max;    // Max update
                min = (this < min) ? this : min;    // Min update
                prev2 = prev1; prev1 = this;        // Number swap for next iteration
            } else {
                dropped++;
            }
        }
        i++;
    }

    if (i > 2)
        printf("Numero massimo: %dn\nNumero minimo: %d\nNumeri scartati: %d", max, min, dropped);
    else
        printf("Errore, non sono stati letti più di due numeri!");
    return 0;
}

int isResult(int a, int b, int res) {               // Checks if res is a possible result of one operation between a and b
    if (res == (a+b) || res == (a-b) || res == (a*b) || (b != 0 && res == (a/b)))
        return 1;
    return 0;
}
