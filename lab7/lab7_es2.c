// LAB 7 ES 2 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#define FILENAME "sort.txt"
#define MAXLEN 100

void InsertionSort(int A[MAXLEN], int N);
void SelectionSort(int A[MAXLEN], int N);
void ShellSort(int A[MAXLEN], int N);

void stampaInfo(int swap,int outIter, int totIter);

int main(void)
{
    FILE *fin;
    int A[MAXLEN], S, N, i, j;

    // Open file
    if ((fin = fopen(FILENAME, "r")) == NULL) {
        printf("ERRORE apertura file di input!");
        return 1;
    }

    // Read array length
    fscanf(fin, "%d", &S);

    // Read and sort
    for (i = 0; i < S; i++) {
        fscanf(fin, "%d", &N);
        for (j = 0; j < N; j++) {
            fscanf(fin, "%d", &A[j]);
        }
        
        InsertionSort(A, N);
        SelectionSort(A, N);
        ShellSort(A, N);

    }
    return 0;
}

void InsertionSort(int A[MAXLEN], int N) {

    int i, j, l = 0, x, r = N - 1;
    int swap = 0, inIter = 0, outIter = 0, totIter = 0;

    printf("-- Insertion sort -- \n");
    for (i = l+1; i <= r; i++) {
        inIter = 0;
        j = i - 1; 
        x = A[i];
        while (x < A[j]) {
            A[j+1] = A[j];
            j--;
            swap++;
            inIter++;
        }
        A[j+1] = x;
        totIter += inIter;
        swap++;
        outIter++;

        printf("Passo %d: %d iterazioni interne\n", i, inIter);
    }
    totIter += outIter;
    stampaInfo(swap, outIter, totIter);
}

void SelectionSort(int A[MAXLEN], int N) {

    int i, j, min, l = 0, r = N - 1;
    int swap = 0, inIter = 0, outIter = 0, totIter = 0;

    printf("-- Selection sort --\n");
    for (i = l; i <= r; i++) {
        inIter = 0;
        for (min = i, j = i + 1; j <= r; j++) {
            if (A[j] < A[min])
                min = j;
                inIter++;
        }
        if (min != i) {
            A[i] = A[min] + A[i] - (A[min] = A[i]);
            swap++;
        }
        printf("Passo %d: %d iterazioni interne\n", i, inIter);
        outIter++;
        totIter += inIter;
    }
    totIter += outIter;
    stampaInfo(swap, outIter, totIter);
}

void ShellSort(int A[MAXLEN], int N) {
    
    int i, j, l = 0, x, r = N - 1, h = 1;
    int swap = 0, inIter = 0, outIter = 0, totIter = 0;

    printf("-- Shell sort --\n");
    // Using Knuth sequence (h(i) = 3*h(i-1) + 1)
    while (h < N/3)
        h = 3 * h + 1;
    
    while (h >= 1) {
        printf("h sequenza: %d\n", h);
        outIter = 0;
        for (i = l + h; i <= r; i++) {
            j = i;
            x = A[i];
            inIter = 0;
            while (j >= l + h && x < A[j-h]) {
                A[j] = A[j - h];
                j -= h;
                swap++;
                inIter++;
            }
            A[j] = x;
            swap++;
            outIter++;
            printf("Passo %d: %d iterazioni interne\n", i, inIter);
            totIter += inIter;
        }
        totIter += outIter;
        h /= 3;
    }
    stampaInfo(swap, outIter, totIter);

}

void stampaInfo(int swap, int outIter, int totIter) {
    printf("Iterazioni esterne %d\n", outIter);
    printf("Tot iterazioni %d\n", totIter);
    printf("Tot scambi %d\n", swap);
}