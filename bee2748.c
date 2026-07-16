#include<stdio.h>
int main(){

    int i;

    for(i=0;i<39;i++){
        printf("-");
    }
    printf("\n");

    printf("|        %-7s%22s|\n", "Roberto", "");
    printf("|%37s|\n", "");
    printf("|        %-4s%25s|\n", "5786", "");
    printf("|%37s|\n", "");
    printf("|        %-6s%23s|\n", "UNIFEI", "");

    for(i=0;i<39;i++){
        printf("-");
    }printf("\n");


    return 0;
}