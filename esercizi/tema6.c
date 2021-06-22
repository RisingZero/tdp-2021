#include <stdio.h>
#include <string.h>
#define MAXM 100

int count(char A[][MAXM], int n, int m, char str[]);

int main(void) {
  char A[][MAXM] = {"xccat","waecq","dtpaz","pcatf"};
  char str[] = "cat";

  int n = count(A, 4, 5, str);
  printf("%d", n);
  return 0;
}

int count(char A[][MAXM], int n, int m, char str[]) {
  int len = strlen(str);
  int i,j, p, valid, cnt = 0;

  // Search on rows
  for (i = 0; i < n; i++) {
    for (j = 0; j <= m - len; j++) {
      if (A[i][j] == str[0]) {
        valid = 1;
        for (p = j; p - j < len && valid; p++) {
          if (A[i][p] != str[p-j])
            valid = 0;
        }
        if (valid)
          cnt++;
      }
    }
  }
  // Search on columns
  for (j = 0; j < m; j++) {
    for (i = 0; i <= n - len; i++) {
      if (A[i][j] == str[0]) {
        valid = 1;
        for (p = i; p - i < len && valid; p++) {
          if (A[p][j] != str[p-i])
            valid = 0;
        }
        if (valid)
          cnt++;
      }
    }
  }
  
  return cnt;
}