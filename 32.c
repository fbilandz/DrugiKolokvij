#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE * f = fopen("indeksi.bin", "rb");
    FILE * f2 = fopen("data.bin", "rb");
    int a, b, c;
    while(fread(&a,sizeof(int), 1, f) == 1){
        fread(&b, sizeof(int), 1, f);
        fread(&c,sizeof(int), 1, f);
        fseek(f2, a, SEEK_SET);
        char * buffer = malloc(a + b + 1);
        fread(buffer, sizeof(char), a + b, f2);
        buffer[a + b] = 0;
        fseek(f2, c, SEEK_SET);
        double vrijednost;
        fread(&vrijednost, 8, 1, f2);
        printf("%s, %lf\n", buffer, vrijednost);
        free(buffer);
    }
    fclose(f);
    fclose(f2);
    return 0;
}