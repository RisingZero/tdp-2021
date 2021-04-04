// LAB 2 Es 2 RAINERI ANDREA ANGELO S280848

#include <stdio.h>

void showSequence(unsigned);

int main(int argc, char const *argv[])
{
    unsigned n, fib_n_rec, fib_n_iter;

    printf("--- SERIE DI FIBONACCI ---\n");
    printf("Inserire n intero positivo: ");
    scanf("%u", &n);

    showSequence(n);
    return 0;
}

void showSequence(unsigned n) {
    if (n == 1)
        printf("%u", 0);
    else if (n == 2)
        printf("%u", 1);
    else {
        unsigned prevprev = 0;
        unsigned prev = 1;
        
        printf("%u %u", prevprev, prev);
        unsigned result = 0;
        for (int i = 2; i < n; i++) {
            result = prevprev + prev;
            prevprev = prev;
            prev = result;
            printf(" %u", result);
        }
    }
}
