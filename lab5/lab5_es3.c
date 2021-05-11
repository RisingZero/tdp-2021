#include<stdio.h>
#include<string.h>
#define max 30
#define maxStr 100

typedef struct i{
    int selettore[2];
    int indice;
    int direzione;
    int posizioni;
} input;

int addTxt(char s[]){    // return is 0 if string not long enough, else 1
    int l = strlen(s);
    if(s[l-1] != 't' || s[l-2] != 'x' || s[l-3] != 't' || s[l-4] != '.'){
        if(l+5 > maxStr) return 0;
        s = strcat(s, ".txt");
    }
    return 1;
}

void stampa_matrice(int M[][max], int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++)
            printf("%d\t", M[i][j]);
        printf("\n");
    }
}

int input_mat(int M[][max], int *c, int *r){
    int i, j;
    char str[max];
    printf("Inserisci il nome del file di input: ");
    scanf("%s", str);addTxt(str);

    FILE *fin;
    if ((fin = fopen(str, "r")) == NULL){
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    
    if(fscanf(fin, " %d %d ", r, c)!=2) return 2;
    //printf("%d - %d\n", r, c);
    for(i=0; i<*r && !feof(fin); i++)
        for(j=0; j<*c; j++)
            fscanf(fin, "%d ", &M[i][j]);
    if(i!=*r) return 3;
    fclose(fin);
}

input selettore(input in, char str[]){
    if(strcmp(str, "riga") == 0){
        in.selettore[0] = 0;
        in.selettore[1] = 1;
    }else if(strcmp(str, "colonna") == 0) {
        in.selettore[0] = 1;
        in.selettore[1] = 0;
    }else if(strcmp(str, "fine") == 0){
        in.selettore[0] = 0;
        in.selettore[1] = 0;
    }else{
        in.selettore[0] = -1;
        in.selettore[1] = -1;
    }
    //printf("%d - %d\n", in.selettore[0], in.selettore[1]);
    return in;
}

int direzione(char str[]){
    if(strcmp(str, "destra") == 0) return 1;
    else if(strcmp(str, "sinistra") == 0) return -1;
    else if(strcmp(str, "giu") == 0) return -1;
    else if(strcmp(str, "su") == 0) return 1;
    printf("Errore direzione, reinserire\n");
    return 0;
}

input input_str(input in){
    char str[max], t[max];
    do{
        printf("Inserisci l'input nella forma: <selettore> <indice> <direzione> <posizioni> e \"fine\" per terminare: ");
        scanf("%s", t);
        in = selettore(in, t);
        if(in.selettore[0] + in.selettore[1] == 0) return in;
        scanf("%d%s%d", &in.indice, str, &in.posizioni);
        in.direzione = direzione(str);
    }while(in.direzione==0 && in.selettore[0] == -1);
    //sta dentro per vero

    return in;
}

void ruota_matrice(int M[][max], int r, int c, input in){
    int N = (in.direzione<=2) ? r : c,
        j = in.indice-1,
        P = in.posizioni,
        dir = in.direzione,
        row, col, i;
    
    if(P>N/2){
        P=N-P;
        dir*=-1;
    }

    for (int iter = 0; iter < P; iter++)
        for (i = (N+dir)%N-1; i != ((N-dir)%N)*dir; i += 1*dir) {
            row = i * in.selettore[0] + j * in.selettore[1];
            col = i * in.selettore[1] + j * in.selettore[0];
            M[row][col] = M[row+in.selettore[0]][col+in.selettore[1]] + M[row][col] - (M[row+in.selettore[0]][col+in.selettore[1]] = M[row][col]);
        }
}

int main(void){
    int M[max][max], c, r, i, j;
    input in;
    
    input_mat(M, &r, &c);
    stampa_matrice(M, r, c);
    in = input_str(in);
    while(in.selettore[0] + in.selettore[1] != 0){
        ruota_matrice(M, r, c, in);
        stampa_matrice(M, r, c);
        in = input_str(in);
    }
    return 0;
}