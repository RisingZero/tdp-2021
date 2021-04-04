// ES 1 LAB 3 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <ctype.h>
#define INPUT "input.txt"
#define OUTPUT "testo.txt"
#define MAXLEN 25

enum flagOpt {NORMAL, SPACE, CAPSPACE, CAPS}; // Valori del flag isPrevSpecial

int main(int argc, char const *argv[])
{
    FILE *fin, *fout;
    char c;
    register int linecounter, realcounter = 0;
    int isPrevSpecial = 0;
    /*  
        linecounter: number of characters in a line of the output (max 25)
        realcounter: number of characters of the original input file written to the output
        isSpecial: flag to indicate if the last character was a punctutation character:
            1   "SPACE"     aggiungere spazio
            2   "CAPSPACE"  aggiungere maiuscola-spazio
            3   "CAPS"      aggiungere solo maiuscola
    */

    if ((fin = fopen(INPUT, "r"))  == NULL) {
        printf("Error opening the input file");
        return 1;
    }

    if ((fout = fopen(OUTPUT, "w")) == NULL) {
        printf("Error opening the output file");
        return 2;
    }

    while (!feof(fin)) {
        // Conto 25 caratteri per riga sul file di output
        for (linecounter = 1; linecounter <= MAXLEN; linecounter++) {
            if ((c = fgetc(fin)) != EOF) {

                // Aggiungo uno spazio se il carattere precedente è un carattere di punteggiatura e non vi è già uno spazio
                if ((isPrevSpecial == SPACE || isPrevSpecial == CAPSPACE) && !isspace(c)) {
                    fputc(' ', fout);
                    linecounter++;
                } 
                if (isspace(c)) {
                    if (c == '\n') {
                        // Completa la riga per andare a capo
                        while (linecounter <= MAXLEN) {
                            fprintf(fout, " ");
                            linecounter++;
                        }
                    } else {
                        // Stampa spazio già presente su input
                        fputc(c, fout);
                    }
                    // Aggiorno il flag isPrevSpecial perché uno spazio è stato inserito
                    isPrevSpecial = (isPrevSpecial == CAPSPACE) ? CAPS : isPrevSpecial;
                    isPrevSpecial = (isPrevSpecial == SPACE) ? NORMAL : isPrevSpecial;

                    realcounter++;
                } else {
                    if (ispunct(c)) {
                        // Controllo segni di punteggiatura
                        isPrevSpecial = (c == '.' || c == '!' || c == '?') ? CAPSPACE : SPACE;
                        fputc(c, fout);
                        realcounter++;
                    } else {
                        //catrattere alfanuemrico
                        c = (isPrevSpecial >= CAPSPACE) ? toupper(c) : c;
                        fputc((isdigit(c)) ? '*' : c, fout); // Sostituzione cifre con *
                        isPrevSpecial = NORMAL; // isPrevSpecial torna al valore normale
                        realcounter++;
                    }
                }
                
                
            } else {
                while (linecounter <= MAXLEN) {
                    fprintf(fout, " ");
                    linecounter++;
                }
            }
        }
        fprintf(fout,"| c:%d\n", realcounter);
        realcounter = 0;
    }

    fclose(fin);
    fclose(fout);
    return 0;
}