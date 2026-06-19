#include<stdio.h>
int main(){

    int hour;

    scanf("%d", &hour);

    if(hour>=0 && hour<=23){
        if(hour>=6 && hour<=18){
            printf("Enter the house\n");
        }
        else{
            printf("Too Dangerous");
        }
    }
    else{
        printf("Input number between (0-23)\n");
    }

    return 0;
}