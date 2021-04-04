// LAB 2 ES 1 RAINERI ANDREA ANGELO S280848

#include <stdio.h>

int mcd(int, int);

int main(int argc, char const *argv[])
{
    int n1, n2, divisore;
    printf("--- CALCOLO MCD ---\n");
    printf("Inserire due interi positivi: \n");
    scanf("%d%d", &n1, &n2);

    divisore = mcd(n1, n2);
    printf("Il M.C.D. tra %d e %d e' %d", n1, n2, divisore);
    return 0;
}

int mcd(x,y) {
    if (x < y) {
        x ^= y;     // Variables swap using bitwise XOR operation
        y ^= x;     // No need of temp variable
        x ^= y;
    }

    if (y == 0) {
        if (x == 0)
            return 0;
        return x;
    }

    return mcd(x % y, y);  // Recursive implementation
}
