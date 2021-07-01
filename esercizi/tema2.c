#include <stdio.h>

void maxOdd(int v[], int N);

int main(void) {

  int v[] = {1,3,7,1,5,0,9,3,1,0};
  maxOdd(v, 10);

  return 0;
}

void maxOdd(int v[], int N) {
  int found = 0, first, i, j, dim, cnt;

  for (dim = N; dim > 0 && !found; dim--) {
    for (first = 0; first <= N - dim;) {
      if (v[first] % 2 != 0) {
        for (i = first, cnt = 0; v[i] % 2 != 0 && cnt != dim; i++, cnt++);
        if (cnt == dim) {
          found = 1;
          printf("{ ");
          for (j = first; j - first < dim; j++) {
            printf("%d ", v[j]);
          }
          printf("}\n");
          first += dim;
        } else {
          first++;
        }
      } else {
        first++;
      }
    }
  }
}