#include <stdio.h>
#include <string.h>

int charErase(char str[], int pos[]);

int main(void) {
  char str[] = "ThisIsAString";
  int pos[] = {7,4,2,0,11,-1};
  int cnt;

  cnt = charErase(str,pos);
  printf("%d %s", cnt, str);

  return 0;
}

int charErase(char str[], int pos[]) {
  int len = strlen(str);
  int i, j, cnt = 0;

  i = 0;
  while (pos[i] != -1) {
    if (pos[i] < len) {
      cnt++;
      for (j = pos[i]; j < len; j++) {
        str[j] = str[j + 1];
      }
      for (j = i; pos[j] != -1; j++) {
        if (pos[j] > pos[i])
          pos[j]--;
      }
      len = strlen(str);
      i++;
    }
  }
  return cnt;
}