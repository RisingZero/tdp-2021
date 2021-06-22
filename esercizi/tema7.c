#include <stdio.h>
#include <string.h>

int conta(char *parole[], int nparole, char *cerca);

int main(int argc, char *argv[]) {
  int cnt;

  cnt = conta(argv+1, argc-2, argv[argc-1]);
  printf("%d", cnt);
  return 0;
}

int conta(char *parole[], int nparole, char *cerca) {
  int i, cnt = 0;
  char *p;

  for (i = 0; i < nparole; i++) {
    // Count substrings in each word
    p = parole[i];
    while ((p = strstr(p, cerca)) != NULL) {
      cnt++;
      p++;
    }
  }
  return cnt;
}