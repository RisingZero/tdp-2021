#include <string.h>
#include <stdio.h>

int strFindSimilar(char str1[], char str2[]) {
    int len1 = strlen(str1), len2 = strlen(str2);
    int i, j, cnt;
    // Cerco in ogni sottostringa di len2 in str1 caratteri uguali con str2
    for (i = 0; i < len1 - len2 + 1; i++) {
        cnt = 0;
    
        for (j = 0; j < len2; j++) {
            if (str1[i+j] == str2[j])
                cnt++;
        }
    
        // Uscita anticipata dalla funzione appena viene identificata la prima sottostringa valida
        if (cnt > len2/2)
            return i;
    }
    
    // Caso finale: nessuna sottostringa valida identificata
    return -1;
    
    }

int main(void) {

    char str1[] = "Seventh";
    char str2[] = "September";
    
    printf("%d", strFindSimilar(str1, str2));
    return 0;
}