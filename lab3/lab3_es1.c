// ES 1 LAB 3 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <ctype.h>
#define INPUT "input.txt"
#define OUTPUT "testo.txt"

int main(int argc, char const *argv[])
{
    FILE *fin, *fout;
    char c;
    int linecounter, realcounter, isPrevSpecial = 0;
    /*  
        linecounter: number of characters in a line of the output (max 25)
        realcounter: number of characters of the original input file written to the output
        isSpecial: flag to indicate if the last character was a punctutation character
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
                if (isPrevSpecial && !isspace(c)) {
                    fputc(' ', fout);
                    linecounter++;
                } 
                if (ispunct(c)) {
                    isPrevSpecial = (c == '.' || c == '!' || c == '?') ? 2 : 1;
                } else {
                    if (isspace(c)) {
                        if (c == '\n') {
                            realcounter++;
                            while (linecounter <= 25) {
                            fprintf(fout, " ");
                            linecounter++;
                            }
                        } else {
                            fputc(c,fout);
                        }
                    } else {
                        c = (isPrevSpecial == 2) ? toupper(c) : c;
                        fputc((isdigit(c)) ? '*' : c, fout);
                        isPrevSpecial = 0;
                    }
                    realcounter++;
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
