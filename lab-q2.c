#include<stdio.h>
int main(){

    int X, Y, Z;
    scanf("%d %d %d", &X, &Y, &Z);

    int ausTotal = X+Z;

    if(ausTotal > Y){
        int need = (ausTotal-Y)+1;
        printf("%d\n", need);
    }else{
        printf("0\n");
    }

    return 0;
}