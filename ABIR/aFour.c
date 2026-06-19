#include<stdio.h>
int main(){


    int battery;

    scanf("%d", &battery);

    if(battery>20){printf("Robot Activated\n");}
    else{printf("Charge Required\n");}


    return 0;
}