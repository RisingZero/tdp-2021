#include <stdio.h>

void InsertionSort(int A[], int N);
void BubbleSort(int A[], int N);
void SelectionSort(int A[], int N);
void ShellSort(int A[], int N);
void BottomUpMergeSort(int A[], int N);
void CountingSort(int A[], int N);
void RadixSort(int A[], int N);

void printVector(int A[], int N);

int main(void) {
  
  const int N = 10;
  int A[] = {1,3,7,2,9,4,6,2,78,10};

  ShellSort(A, N);
  printVector(A, N);
  return 0;
}

void InsertionSort(int A[], int N) {
  int i, j, l = 0, r = N-1, x;
  for (i = l + 1; i <= r; i++) {
    x = A[i];
    for (j = i - 1; j >= l && A[j] > x; j--) {
      A[j + 1] = A[j];
    }
    A[j + 1] = x;
  }
}

void BubbleSort(int A[], int N) {
    int i, j, l = 0, r = N-1, temp;
    for (i = l; i < r; i++) {
        for (j = l; j < r - i + l; j++) {
            if (A[j] > A[j + 1]) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }
    }
}

void SelectionSort(int A[], int N) {
    int i, j, l = 0, r = N-1, min, temp;
    for (i = l; i < r; i++) {
        min = i;
        for (j = i + 1; j <= r; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
}

void ShellSort(int A[], int N) {
    int i, j, h = 1, x, l = 0, r = N-1;
    // Sequenza di Knuth
    // h_i = 3h_{i-1} + 1
    while (h < N/3)
        h = 3*h + 1;

    while (h >= 1) {
        for (i = l + h; i <= r; i++) {
            x = A[i];
            for (j = i - h; j >= l && A[j] > x; j -= h) {
                A[j+h] = A[j];
            }
            A[j+h] = x;
        }
        h = h/3;
    }
}



void printVector(int A[], int N) {
  for (int i = 0; i < N; i++) {
    printf("%d ", A[i]);
  }
  printf("\n");
}