#include <stdio.h>

int main(){

    int day;
    scanf("%d", &day);

    if(day>7){
        printf("7\n");
    }else{
        printf("%d\n", day);
    }

    return 0;
}