// LAB 2 ES 4 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <ctype.h>

int codifica(FILE *fin, FILE *fout);
int decodifica(FILE *fin, FILE *fout);

int main(int argc, char const *argv[])
{
    FILE *fin, *fout;
    char opt, input_file[25], output_file[25];
    int esito;
    int valido = 0;

    printf("--- CODIFICA E DECODIFICA FILE ---\n");
    
    while (valido == 0) {
        printf("Scegliere una opzione tra le seguenti\nC per codificare\nD per decodificare\n");
        printf("Inserire opzione: ");
        scanf("%c", &opt);  // Lettura opzione da utente

        while (getchar() != '\n'); // Clear input buffer

        printf("Inserire il nome del file di input e di output: \n");
        scanf("%s%s", input_file, output_file);

        if ((fin = fopen(input_file, "r")) == NULL) {
            printf("ERRORE in apertura del file di input\n");
            return 1;
        }

        if ((fout = fopen(output_file, "w")) == NULL) {
            printf("ERRORE in apertura del file di output\n");
            return 2;
        }

        switch (opt) {
            case 'C':
                valido = 1;
                esito = codifica(fin, fout);
                if (esito == 0)
                    printf("ERRORE nella codifica, nessun dato emesso in output\n");
                else
                    printf("Codifica completata correttamente, %d caratteri in output\n", esito);
                break;

            case 'D':
                valido = 1;
                esito = decodifica(fin, fout);
                if (esito == 0)
                    printf("ERRORE nella decodifica, nessun dato emesso in output\n");
                else
                    printf("Decodifica completata correttamente, %d caratteri in output\n", esito);
                break;

            default:
                printf("ERRORE: inserita una opzione non valida!\n");
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}

int codifica(FILE *fin, FILE *fout) {

    char c, previous;
    int counter, k, h;
    counter = h = k = 0;

    if (!feof(fin)) {
        c = fgetc(fin);
        if (isdigit(c))
            k++;
        fputc(c, fout);
        counter++;
        previous = c;
    } else {
        return counter; // Ritorna 0 se il file da codificare è vuoto
    }

    while (!feof(fin)) {
        c = fgetc(fin);
        if (c != EOF) { // fgetc() returns EOF also if an error occurs in reading the file, not only at the end of the file
            if (isdigit(c)) {
                fputc((char)('0' + (c - '0' + k++)%10), fout);
            } else if (isalpha(c)) {
                if (isalpha(previous)) {
                    if (isupper(c)) {
                        h = (isupper(previous)) ? previous - 'A' : previous - 'a';
                        c = (char)('A' + (c - 'A' + h)%26);
                        fputc(c, fout);
                    } else {
                        h = (isupper(previous)) ? previous - 'A' : previous - 'a';
                        c = (char)('a'+ (c - 'a' + h)%26);
                        fputc(c, fout);
                    }
                } else {
                    fputc(c, fout);
                }
            } else {
                fputc(c, fout);
            }
            counter++;
            previous = c;
        }
    }
    return counter;
}

//FIXME: correggere decodifica
int decodifica(FILE *fin, FILE *fout) {
    char c, previous;
    int counter, k ,h;
    counter = k = h = 0;

    if (!feof(fin)) {
        c = fgetc(fin);
        if (isdigit(c))
            k--;
        fputc(c, fout);
        counter++;
        previous = c;
    } else {
        return counter; // Ritorna 0 se il file da decodificare è vuoto
    }

    while (!feof(fin)) {
        c = getc(fin);
        if(c != EOF) {
            if (isdigit(c)) {
                fputc((char)('0' + (c - '0' + k--)%10), fout);
            } else if (isalpha(c)) {
                if (isalpha(previous)) {
                    if (isupper(c)) {
                        h = (isupper(previous)) ? previous - 'A' : previous - 'a';
                        //c = (char)('A' + (c - 'A' - h)%26);
                        fputc((char)('A' + (c - 'A' - h)%26), fout);
                    } else {
                        h = (isupper(previous)) ? previous - 'A' : previous - 'a';
                        //c = (char)('a' + (c - 'a' - h)%26);
                        fputc((char)('a' + (c - 'a' - h)%26), fout);
                    }
                } else {
                    fputc(c, fout);
                }
            } else {
                fputc(c, fout);
            }
            counter++;
            previous = c;
        }
    }
    
    return counter;
}