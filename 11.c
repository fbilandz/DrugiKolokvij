#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id_broj;
    char naziv[32];
    char oznaka;
    double vrijednost;
} zapis;

int compare(zapis * z1, zapis * z2){
    if(z1->vrijednost > z2->vrijednost) return 1;
    if(z2->vrijednost > z1->vrijednost) return -1;
    return 0;
}

int main(){
    FILE * f1 = fopen("zapisi1.bin", "rb");
    if(!f1) return 1;
    FILE * f2 = fopen("zapisi2.bin", "rb");
    if(!f2) return 1;
    fseek(f1, 0, SEEK_END);
    fseek(f2, 0, SEEK_END);
    long l1 = ftell(f1);
    long l2 = ftell(f2);
    fseek(f1, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);
    zapis * z = (zapis *) malloc(l1 + l2);
    fread(z, sizeof(zapis), l1/sizeof(zapis), f1);
    z += l1/sizeof(zapis);
    fread(z, sizeof(zapis), l2/sizeof(zapis), f2);
    z -= l1/sizeof(zapis);
    qsort(z, (l1+l2)/sizeof(zapis), sizeof(zapis), (int (*)(const void *, const void *))compare);
    FILE * f = fopen("zapisi.bin", "wb");
    if(!f) return 1;
    fwrite(z, sizeof(zapis), (l1+l2)/sizeof(zapis), f);
    free(z);
    fclose(f);
    fclose(f1);
    fclose(f2);
    return 0;
}