#include <stdio.h>
#include <math.h>
#define MAXL 50
#define MAXP 100

typedef struct product_s {
    char type[MAXL];
    int quantity;
    float price;
} Product;

int readStoreLog(Product store[], char *filename);
void orderProducts(Product store[], int storeDim, int filter);
void showStore(Product store[], int storeDim);

int main(int argc, char *argv[]) {

    Product store[MAXP];
    int storeDim, filter;

    if ((storeDim = readStoreLog(store, argv[1])) == -1) {
        printf("ERRORE in apertura file\n");
        return 1;
    }
    
    do {
        printf("Come si vuole mostrare il magazzino?\n");
        printf("0) In ordine di quantità di prodotti venduti\n");
        printf("1) In ordine di incasso relativo al prodotto venduto\n");
        printf("-1) EXIT\n");
        printf("-> ");
        scanf("%d", &filter);

        if (filter == 0 || filter == 1) {
            orderProducts(store, storeDim, filter);
            showStore(store, storeDim);
        } else {
            if (filter != -1)
                printf("ERRORE: comando non riconosciuto");
        }
    } while (filter != -1);

    printf("Grazie per aver utilizzato il nostro software!");
    return 0;
}

int readStoreLog(Product store[MAXP], char *filename) {
    FILE *fp;
    int dim = 0;

    if ((fp = fopen(filename, "r")) == NULL)
        return -1;

    while (fscanf(fp, "%s %d %f", store[dim].type, &store[dim].quantity, &store[dim].price) == 3)
        dim++;

    fclose(fp);
    
    return dim;
}

void orderProducts(Product store[MAXP], int storeDim, int filter) {
    int l = 0, r = storeDim - 1, i, j;
    Product x;
    
    for (i = l + 1; i <= r; i++) {
        x = store[i];
        for (j = i - 1; j >= l && ((store[j].quantity * pow(store[j].price, filter)) > (x.quantity * pow(x.price, filter))); j--) {
            store[j + 1] = store[j];
        }
        store[j + 1] = x;
    }
}

void showStore(Product store[], int storeDim) {
    int i;

    for (i = 0; i < storeDim; i++) {
        printf("%s %d %.2f\n", store[i].type, store[i].quantity, store[i].price);
    }
}