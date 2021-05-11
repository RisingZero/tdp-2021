// LAB 5 ES 2 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <string.h>
#define MAXLEN_RIGA 200
#define MAX_RICODIFICHE 30
#define WORDLEN 25
#define dictname "dizionario.txt"
#define infilename "sorgente.txt"
#define outfilename "ricodificato.txt"

typedef struct {
    char originale[WORDLEN];
    char ricodifica[WORDLEN];
} Transform;

int leggiDizionario(FILE *fin, Transform dizionario[]);
void ricodifica(FILE *fin, FILE *fout, Transform dizionario[], int dictlen);

int main(void) {

    FILE *fin, *dict, *fout;
    Transform dizionario[MAX_RICODIFICHE];
    int dictlen;

    if ((dict = fopen(dictname, "r")) == NULL) {
        printf("Errore apertura file dizionario");
        return 1;
    }

    dictlen = leggiDizionario(dict, dizionario);

    if ((fin = fopen(infilename, "r")) == NULL) {
        printf("Errore apertura file di input");
        return 1;
    }

    if ((fout = fopen(outfilename, "w")) == NULL) {
        printf("Errore apertura file di output");
        return 2;
    }

    ricodifica(fin, fout, dizionario, dictlen);

    fclose(fin);
    fclose(fout);
    fclose(dict);

    return 0;
}

int leggiDizionario(FILE *fin, Transform dizionario[]){
    /* 
        Lettura ricodifiche da file
     */

    int nCodifiche, i;

    fscanf(fin, "%d", &nCodifiche);

    for (i = 0; i < nCodifiche; i++) {
        fscanf(fin, "%s %s", dizionario[i].ricodifica, dizionario[i].originale);
    }

    return nCodifiche;
}

void ricodifica(FILE *fin, FILE *fout, Transform dizionario[], int dictlen) {

    char riga[MAXLEN_RIGA + 1], temp[MAXLEN_RIGA + 1] = "", *pos, *nextPos, *tempPos;
    int i, j;

    while (fgets(riga, MAXLEN_RIGA, fin) != NULL) {
        for (i = 0; i < dictlen; i++) {
            pos = riga;
            tempPos = temp;
            while ((nextPos = strstr(pos, dizionario[i].originale)) != NULL) {

                while (pos != nextPos) {
                    *tempPos = *pos;
                    pos++; tempPos++;
                }

                pos += strlen(dizionario[i].originale);
                
                for (j = 0; j < strlen(dizionario[i].ricodifica); j++, tempPos++) {
                    *tempPos = dizionario[i].ricodifica[j];
                }
            }

            while (pos != (riga + MAXLEN_RIGA + 1)) {
                *tempPos = *pos;
                pos++; tempPos++;
            }

            strcpy(riga, temp);
            strcpy(temp, "");
        }
        
        fprintf(fout, "%s", riga);
    }
}