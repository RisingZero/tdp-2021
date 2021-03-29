// LAB 2 ES 3 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#define FILENAME_CHIARO "sorgente.txt"
#define FILENAME_COMPRESSO "compresso.txt"
#define FILENAME_DECOMPRESSO "decompresso.txt"

int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main(int argc, char const *argv[])
{
    FILE *fin, *fout;
    char opt;
    int valido = 0;
    int esito;

    printf("--- COMPRESSIONE E DECOMPRESSIONE FILE ---\n");

    while (!valido) {
        printf("Indicare una opzione tra le seguenti\nC compressione\nD decompressione\n");
        printf("Inserire comando: ");
        scanf("%c", &opt);

        switch (opt) {
            case 'C':
                printf("COMPRESSIONE\n");

                if ((fin = fopen(FILENAME_CHIARO, "r"))  == NULL){
                    printf("ERRORE nell'apertura del file di input");
                    return 1;
                }

                if ((fout = fopen(FILENAME_COMPRESSO, "w"))  == NULL){
                    printf("ERRORE nell'apertura del file di output");
                    return 2;
                }

                if ((esito = comprimi(fin, fout)) == 0)
                    printf("ERRORE: nessun dato è stato scritto in output");
                else
                    printf("Compressione eseguita correttamente, sono stati scritti %d caratteri in output", esito);
                
                valido = 1;
                break;

            case 'D':
                printf("DECOMPRESSIONE\n");

                if ((fin = fopen(FILENAME_COMPRESSO, "r"))  == NULL){
                    printf("ERRORE nell'apertura del file di input");
                    return 1;
                }

                if ((fout = fopen(FILENAME_DECOMPRESSO, "w"))  == NULL){
                    printf("ERRORE nell'apertura del file di output");
                    return 2;
                }

                if ((esito = decomprimi(fin, fout)) == 0)
                    printf("ERRORE: nessun dato è stato scritto in output");
                else
                    printf("Decompressione eseguita correttamente, sono stati scritti %d caratteri in output", esito);

                valido = 1;
                break;

            default:
                printf("ERRORE: opzione non valida\n");
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}

int comprimi(FILE *fin, FILE *fout) {
    char c, previous;
    int repet = 0; // Conta il numero di ripetizioni di un carattere
    int counter = 0; // Conta i caratteri scritti sull'output

    if (!feof(fin))
        previous = fgetc(fin);
    else
        return 0; // Ritorna 0 se il file da compirmiere è vuoto
    
    while (!feof(fin)) {    
        if ((c = fgetc(fin)) == previous && repet < 9){
            repet++;
        } else if (c == previous && repet == 9) {
            fprintf(fout, "%c$%d", previous, repet);
            counter += 3;
            repet = 0;
        } else {
            fputc(previous, fout);
            counter++;
            if (repet > 1){  
                fprintf(fout, "$%d", repet);
                counter += 2;
            } else if (repet == 1) {
                fputc(previous, fout);
                counter++;
            }
            repet = 0;
            previous = c;
        }
        }
    return counter;
}

int decomprimi(FILE *fin, FILE *fout) {
    char c, previous, number;
    int repet, i;
    int counter = 0; // Conta i caratteri scritti sull'output

    if (!feof(fin))
        previous = fgetc(fin);
    else
        return 0; // Ritorna 0 se il file da decomprimere è vuoto
    
    while (!feof(fin)) {
        c = fgetc(fin);
        if (c == '$') {
            if (isdigit(number = fgetc(fin)))
                repet = number - '0'; // Legge il numero di ripetizioni indicato dopo il '$'
            else
                return 0;  // Se dopo il carattere '$' non vi è un numero il file ha un errore di codifica

            for (i = 0; i <= repet; i++) {
                fputc(previous, fout);
                counter++;
            }
            if (!feof(fin))
                previous = fgetc(fin);  
        } else {
            fputc(previous, fout);
            counter++;
            previous = c;
        }
    }
    return counter;
}