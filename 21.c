#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char broj_poglavlja[16];
    char naziv_poglavlja[256];
} zapis;

int cmp(int i, int j){
    return i - j;
}
int compare(zapis * z1, zapis * z2){
    int s11, s12, s13, s21, s22, s23;
    sscanf(z1->broj_poglavlja, "%d.%d.%d", &s11, &s12, &s13);
    sscanf(z2->broj_poglavlja, "%d.%d.%d", &s21, &s22, &s23);
    if(!cmp(s11, s21)){
        if(!cmp(s12, s22)){
            return cmp(s13, s23);
        }
        return cmp(s12, s22);
    }
    return cmp(s11, s21);
}

int main(){
    FILE * f = fopen("zapisi.bin", "rb");
    if(!f) return 1;
    fseek(f, 0, SEEK_END);
    long l = ftell(f);
    fseek(f, 0, SEEK_SET);
    zapis * z = malloc(l);
    fread(z, sizeof(zapis), l/sizeof(zapis), f);
    qsort(z, l/sizeof(zapis), sizeof(zapis), (int (*)(const void *, const void *))compare);
    fclose(f);
    f = fopen("zapisi.bin", "wb");
    fwrite(z, sizeof(zapis), l/sizeof(zapis), f);
    int i;
    for(i = 0; i < l/sizeof(zapis); i++){
        printf("%s %s\n", z[i].broj_poglavlja, z[i].naziv_poglavlja);
    }
    free(z);
    fclose(f);
    return 0;
}
