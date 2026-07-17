#include <stdio.h>
 
int main() {
 
    int sec, hours = 0, min=0;
    
    scanf("%d", &sec);
    
    if(sec>=3600){
        hours = sec/3600;
        sec = sec - (hours*3600);
    }
    if(sec>=60){
        min = sec/60;
        sec = sec-(min*60);
    }


    printf("%d:%d:%d\n", hours, min, sec);
 
    return 0;
}