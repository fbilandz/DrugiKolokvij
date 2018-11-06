#include <stdio.h>
int main(){
int x = 4, y = 1, z[6] = {-1,3,0,2,5,42};
int *j = z;
for(int x = 0; x < 7; x++){
x += 1;
y = (2*x+3)%4;
*j++;
*(j+y) -= 2;
y--;
}
for(y = 0; y < 3; y++){
x = z[y];
z[y] = z[5-y];
z[5-y] = x;
}
printf("%2d%2d%2d", z[0], z[1], z[3]);
return 0;
}