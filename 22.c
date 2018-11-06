#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char naziv[32];
    double vrijednost;
} zapis;

int main(){
    FILE * f1 = fopen("nazivi.bin", "rb"); if(!f1) return 1;
    FILE * f2 = fopen("brojevi.bin", "rb"); if(!f2) return 1;
    FILE * f3 = fopen("vrijednosti.bin", "rb"); if(!f3) return 1;
    fseek(f2, 0, SEEK_END);
    long l = ftell(f2);
    int N = l / sizeof(unsigned long); if(N * sizeof(unsigned long) != l) return 2;
    fseek(f2, 0, SEEK_SET);
    zapis * z = malloc(N * sizeof(zapis)); if(!z) return 3;
    int i;
    for(i = 0; i < N; i++){
        unsigned long x, a;
        char naziv[32];
        double vrijednost;
        fread(&x, sizeof(unsigned long), 1, f2);
        if(x > 31) a = 31;
        else a = x;
        fread(naziv, sizeof(char), a, f1);
        naziv[a] = '\0';
        fread(&vrijednost, sizeof(double), 1, f3);
        if(x > a) f1 += a - x;
        strcpy(z[i].naziv, naziv);
        z[i].vrijednost = vrijednost;
    }
    FILE * f = fopen("nv.bin", "wb");

    fwrite(z, sizeof(zapis), N, f);
    free(z);
    fclose(f);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}