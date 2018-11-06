#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double vrijednost;
    long duljina_naziva;
} zapis;

int main(){
    FILE * f = fopen("zapisi.bin", "rb");
    if(!f) return 1;
    zapis z;
    while(fread(&z, sizeof(zapis), 1, f) == 1){
        char * buffer = malloc(z.duljina_naziva + 1);
        buffer[z.duljina_naziva] = 0;
        fread(buffer, sizeof(char), z.duljina_naziva, f);
        printf("%s, %lf\n", buffer, z.vrijednost);
        free(buffer);
    }
    fclose(f);

    return 0;
}