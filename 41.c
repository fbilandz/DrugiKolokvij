#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char oznaka[16];
    double v1, v2, v3;
} zapis;

int compare(zapis * a, zapis * b){
    int va = a->v1 + a->v2 + a->v3;
    int vb = b->v1 + b->v2 + b->v3;
    if(va > vb) return -1;
    if(va < vb) return 1;
    return 0;
}

int main(){
    FILE * f = fopen("zapisi.bin", "rb"); if(!f) return 1;
    fseek(f, 0, SEEK_END);
    long l = ftell(f);
    fseek(f, 0, SEEK_SET);
    zapis * z = malloc(l);
    int N = l / sizeof(zapis);
    fread(z, sizeof(zapis), N, f);
    qsort(z, N, sizeof(zapis), (int (*)(const void *, const void *))compare);
    int i;
    for(i = 0; i < N; i++){
        printf("%s %lf\n", z[i].oznaka, z[i].v1 + z[i].v2 + z[i].v3);
    }
    free(z);
    fclose(f);
    return 0;
}