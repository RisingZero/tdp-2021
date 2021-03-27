// ES 1 LAB 3 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <ctype.h>
#define INPUT "input.txt"
#define OUTPUT "testo.txt"

int main(int argc, char const *argv[])
{
    FILE *fin, *fout;
    char c;
    register int linecounter, realcounter = 0;
    int isPrevSpecial = 0;
    /*  
        linecounter: number of characters in a line of the output (max 25)
        realcounter: number of characters of the original input file written to the output
        isSpecial: flag to indicate if the last character was a punctutation character
            1   aggiungere spazio
            2   aggiungere maiuscola-spazio
            3   aggiungere solo maiuscola
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
        for (linecounter = 1; linecounter <= 25; linecounter++) {
            if ((c = fgetc(fin)) != EOF) {

                if ((isPrevSpecial==1 || isPrevSpecial==2) && !isspace(c)) {
                    fputc(' ', fout);
                    linecounter++;
                } 
                if (isspace(c)) {
                    if (c == '\n') {
                        //\n e completa la riga
                        while (linecounter <= 25) {
                            fprintf(fout, " ");
                            linecounter++;
                        }
                    } else {
                        //stampa spazio
                        fputc(c, fout);
                        //fprintf(fout, "(%d)", isPrevSpecial);
                    }
                    //mette maiuscolo senza spazio
                    isPrevSpecial = (isPrevSpecial == 2) ? 3 : isPrevSpecial;
                    //non mette lo spazio perché gia messo
                    isPrevSpecial = (isPrevSpecial == 1) ? 0 : isPrevSpecial;
                    realcounter++;
                } else {
                    if (ispunct(c)) {
                        //punteggiatura
                        isPrevSpecial = (c == '.' || c == '!' || c == '?') ? 2 : 1;
                        fputc(c, fout);
                        realcounter++;
                    } else {
                        //catrattere alfanuemrico
                        c = (isPrevSpecial >=2) ? toupper(c) : c;
                        fputc((isdigit(c)) ? '*' : c, fout);
                        isPrevSpecial = 0;
                        realcounter++;
                    }
                }
                
                
            } else {
                while (linecounter <= 25) {
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