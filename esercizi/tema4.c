#include <stdio.h>
#include <string.h>

void countAndPrint(char str[], int n);

int main(void) {

  char s[] = "forExample";
  int n = 4;

  countAndPrint(s, n);
  return 0;
}

int isVowel(char c) {
    switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            return 1;
        default:
            return 0;
    }
}

void countAndPrint(char str[], int n) {
  int len = strlen(str);
  int i, j = 0, cnt = 0;

  for (i = 0; i < len - n; i++) {
    for (j = i; j - i < n; j++) {
      if (isVowel(str[j])) {
        cnt++;
      }
    }
    if (cnt == 2) {
      for (j = i; j - i < n; j++) {
        printf("%c", str[j]);
      }
      printf("\n");
    }
    cnt = 0;
  }
}