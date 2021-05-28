// LAB 8 ES 2 RAINERI ANDREA ANGELO S280848

#include <stdio.h>
#define MAX_SIZE 64
#define BYTE 8

int checkEndianness();
void stampaCodifica(void *p, int size, int bigEndian);
void readBits(unsigned char *pchar, char *bit);

int main(int argc, char const *argv[])
{
    float af, num;
    double ad;
    int bigEndian = checkEndianness(), exp;
    
    printf("Dimensione float: %d byte, %d bit\n", sizeof(af), sizeof(af)*8);
    printf("Dimensione double: %d byte, %d bit\n", sizeof(ad), sizeof(ad)*8);

    printf("Inserire numero: ");
    scanf("%f E%d", &num, &exp);
    ad = af = num * (10^exp);

    stampaCodifica((void *) &af, sizeof(af), bigEndian);
    stampaCodifica((void *) &ad, sizeof(ad), bigEndian);

    return 0;
}

int checkEndianness() {
    
    int test = 1;
    char *pbyte = (char *)&test;

    if (*pbyte == 0)
        return 0;
    else
        return 1;

}

/* 
    Function to get binary representation of the content of a byte
    as char vector
 */
void readBits(unsigned char *pchar, char *bit) {
    int i = BYTE;

    while(i--) {
        *(bit++) = '0' + ((*pchar >> i) & 1);
    }
    
    *bit = '\0';
}

void stampaCodifica(void *p, int size, int bigEndian) {

    unsigned char *pchar = (unsigned char *)p;
    char *bit, bits[MAX_SIZE + 1];
    int i, byteDir = 1;

    //  Endianness check in byte reading direction
    if (!bigEndian) {
        byteDir = -1;
        pchar += size;
    }

    // Build vector with bit representation of the whole number
    for (i = 0, bit = bits; i < size; i += byteDir, bit += 8) {
        readBits(pchar + i, bit);
    }

    printf("%s\n", bits);
}