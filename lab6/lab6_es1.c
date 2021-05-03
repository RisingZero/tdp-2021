// LAB 6 ES 1 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#include <string.h>
#define filename "log.txt"
#define MAXLEN 30
#define MAX_DATA 1000

typedef struct {
    char codice[MAXLEN];
    char partenza[MAXLEN];
    char destinazione[MAXLEN];
    short data[3];
    short ora_partenza[3];
    short ora_arrivo[3];
    int ritardo;
} Tratta;

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comando_e;

/*
    Utility functions for 
        - readfile 
        - menu handling
        - datashow
 */
int letturaFile(FILE *fin, Tratta []);
void menuParola(Tratta [], int);
comando_e leggiComando();
void showOptions();
void printTrip(Tratta);

/* 
    Features functions
 */
void findBetween(Tratta [], int);
void findFrom(Tratta [], int);
void findTo(Tratta [], int);
void findLateBetween(Tratta [], int);
void findDelayWithID(Tratta [], int);

/* 
    Support functions
 */
int isBetween(short [], short [], short []);

int main(int argc, char const *argv[])
{
    FILE *fin;
    int nTratte;
    Tratta tratte[MAX_DATA];

    if ((fin = fopen(filename, "r")) == NULL) {
        printf("ERRORE in apertura file di input");
        return 1;
    }

    nTratte = letturaFile(fin, tratte);

    menuParola(tratte, nTratte);

    return 0;
}

int letturaFile(FILE *fin, Tratta tratte[]) {
    int n, i;

    // Lettura numero tratte dalla prima riga
    fscanf(fin, "%d", &n);

    for (i = 0; i < n; i++) {
        fscanf(fin, "%s %s %s %hd/%hd/%hd %hd:%hd:%hd %hd:%hd:%hd %d",
            tratte[i].codice,
            tratte[i].partenza,
            tratte[i].destinazione,
            &tratte[i].data[0],  &tratte[i].data[1], &tratte[i].data[2],
            &tratte[i].ora_partenza[0],  &tratte[i].ora_partenza[1], &tratte[i].ora_partenza[2],
            &tratte[i].ora_arrivo[0],  &tratte[i].ora_arrivo[1], &tratte[i].ora_arrivo[2],
            &tratte[i].ritardo);
    }

    return n;
}

void menuParola(Tratta tratte[], int nTratte) {
    comando_e comando;

    comando = leggiComando();
    while (comando != r_fine) {

        switch (comando) {
            case r_date:
                findBetween(tratte, nTratte);
                break;
            case r_partenza:
                findFrom(tratte, nTratte);
                break;
            case r_capolinea:
                findTo(tratte, nTratte);
                break;
            case r_ritardo:
                findLateBetween(tratte, nTratte);
                break;
            case r_ritardo_tot:
                findDelayWithID(tratte, nTratte);
                break;
        }

        comando = leggiComando();
    }
}

comando_e leggiComando() {

    int valid;
    char input[MAXLEN];
    comando_e comando;

    do {
        showOptions();
        scanf("%s", input);
        valid = 1;

        if (strcmp(input, "date") == 0)
            comando = r_date;
        else if (strcmp(input, "partenza") == 0)
            comando = r_partenza;
        else if (strcmp(input, "capolinea") == 0)
            comando = r_capolinea;
        else if (strcmp(input, "ritardo") == 0)
            comando = r_ritardo;
        else if (strcmp(input, "ritardo_tot") == 0)
            comando = r_ritardo_tot;
        else if (strcmp(input, "fine") == 0)
            comando = r_fine;
        else {
            valid = 0;
            printf("Errore: comando non valido\n");
        }
    } while(!valid);
        
        return comando;
}

void showOptions() {
    printf("Opzioni: \n");
    printf("date <data1> <data2> -> Elenca tutte le corse nell'intervallo temporale indicato\n");
    printf("partenza <fermata> -> Elenca le corse partite da una fermata\n");
    printf("capolinea <fermata> -> Elenca le corse con una specifica destinazione\n");
    printf("ritardo <data1> <data2> -> Elenca tutte le corse con ritardo nell'intervallo temporale indicato\n");
    printf("ritardo_tot <codice> -> Mostra il ritardo complessivo accumulato dalle corse identificate dal codice tratta indicato\n");
    printf("fine -> Termina il programma\n");
    printf("Inserire un comando: \n");
}

void printTrip(Tratta tratta) {
    /* 
        Function to print a given trip info
     */

    printf("%s %s %s %hd/%hd/%hd %hd:%hd:%hd %hd:%hd:%hd Ritardo %d\n",
        tratta.codice, tratta.partenza, tratta.destinazione,
        tratta.data[0], tratta.data[1], tratta.data[2],
        tratta.ora_partenza[0], tratta.ora_partenza[1], tratta.ora_partenza[2],
        tratta.ora_arrivo[0], tratta.ora_arrivo[1], tratta.ora_arrivo[2],
        tratta.ritardo);
}

void findBetween(Tratta tratte[], int nTratte) {
    short inizio[3], fine[3];
    int i, count = 0;

    if (scanf("%hd/%hd/%hd %hd/%hd/%hd", &inizio[0], &inizio[1], &inizio[2], &fine[0], &fine[1], &fine[2]) == 6) {
        for (i = 0; i < nTratte; i++) {
            if (isBetween(inizio, fine, tratte[i].data)) {
                    printTrip(tratte[i]);
                    count++;
            }
        }

        if (count == 0)
            printf("Nessuna tratta trovata nell'intervallo indicato\n");

    } else {
        printf("Errore, il comando inserito non è completo o correttamente formattato!\n");
    }
}

void findFrom(Tratta tratte[], int nTratte) {
    int i, count = 0;
    char fermata[MAXLEN];

    if (scanf("%s", fermata) == 1) {
        for (i = 0; i < nTratte; i++) {
            if (strcmp(tratte[i].partenza, fermata) == 0) {
                printTrip(tratte[i]);
                count++;
            }
        }

        if (count == 0)
            printf("Nessuna tratta trovata con partenza: %s\n", fermata);

    } else {
        printf("Errore, il comando inserito non è completo o correttamente formattato!\n");
    }
}

void findTo(Tratta tratte[], int nTratte) {
    int i, count = 0;
    char fermata[MAXLEN];

    if (scanf("%s", fermata) == 1) {
        for (i = 0; i < nTratte; i++) {
            if (strcmp(tratte[i].destinazione, fermata) == 0) {
                printTrip(tratte[i]);
                count++;
            }
        }

        if (count == 0)
            printf("Nessuna tratta trovata con capolinea: %s\n", fermata);
            
    } else {
        printf("Errore, il comando inserito non è completo o correttamente formattato!\n");
    }
}

void findLateBetween(Tratta tratte[], int nTratte) {
    short inizio[3], fine[3];
    int i, count = 0;

    if (scanf("%hd/%hd/%hd %hd/%hd/%hd", &inizio[0], &inizio[1], &inizio[2], &fine[0], &fine[1], &fine[2]) == 6) {
        for (i = 0; i < nTratte; i++) {
            if (tratte[i].ritardo > 0) {
                if (isBetween(inizio, fine, tratte[i].data)) {
                    printTrip(tratte[i]);
                    count++;
                }
            }
        }

        if (count == 0)
            printf("Nessuna tratta con ritardo trovata nell'intervallo indicato\n");
            
    } else {
        printf("Errore, il comando inserito non è completo o correttamente formattato!\n");
    }
}

void findDelayWithID(Tratta tratte[], int nTratte) {
    int i, count = 0, delay = 0;
    char codice[MAXLEN];

    if (scanf("%s", codice) == 1) {
        for (i = 0; i < nTratte; i++) {
            if (strcmp(tratte[i].codice, codice) == 0) {
                delay += tratte[i].ritardo;
                count++;
            }
        }

        if (count > 0)
            printf("Il ritardo complessivo accumulato sulla tratta %s è di %d minuti\n", codice, delay);
        else
            printf("Nessuna tratta trovata con il codice %s\n", codice);

    } else {
        printf("Errore, il comando inserito non è completo o correttamente formattato!\n");
    }
}

int isBetween(short firstDate[], short lastDate[], short date[]) {
    /* 
        Function to verify if a date is between two given dates
        @params:
            firstDate : (short []) first date of the range
            lastDate : (short []) last date of the range
            date : (short []) date to verify

        Date format: [yyyy,mm,dd]

        @return:
            int : 
                1 -> Date is in range (True)
                0 -> Date is not in range (False)

     */
    enum bool {False, True};

    int first = firstDate[0]*10000 + firstDate[1]*100 + firstDate[2];
    int last = lastDate[0]*10000 + lastDate[1]*100 + lastDate[2];
    int today = date[0]*10000 + date[1]*100 + date[2];

    if (today >= first && today <= last)
        return True;
    else
        return False;
}
