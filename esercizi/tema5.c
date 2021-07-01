#include <stdio.h>

void prodCartOrd(int *v1, int d1, int *v2, int d2);

int main(void) {
  int v1[] = {2,1,3};
  int v2[] = {6,4,3,6};

  prodCartOrd(v1, 3, v2, 4);
  return 0;
}

void prodCartOrd(int *v1, int d1, int *v2, int d2) {
  int prod[100][100] = {0};
  int i, j, max1 = 0, max2 = 0, n;

  for (i = 0; i < d1; i++) {
    for (j = 0; j < d2; j++) {
      prod[v2[j]][v1[i]] = 1;
      max1 = (v1[i] > max1) ? v1[i] : max1;
      max2 = (v2[j] > max2) ? v2[j] : max2;

    }
  }

  for (n = 0; n <= max1+max2; n++) {
    for (j = 0; j <= max1; j++) {
      i = n - j;
      if (prod[i][j] == 1)
        printf("(%d,%d)\n", j,i);
      }
    }
}
