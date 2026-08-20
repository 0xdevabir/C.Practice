#include<stdio.h>
#include<string.h>
int main(){

    char a[100], b[100];

    scanf("%s %s", a, b);

    
    int al = strlen(a);
    int bl = strlen(b);

    int maxOne=al;
    if(al>bl){
        maxOne=al;
    }else{maxOne=bl;}

    int same=0;

    for(int i=0;i<=maxOne;i++){
        if(a[i] != b[i]){
            same = 1;
            break;
        }
    }

    if(same==0){
        printf("Same");
    }else{printf("different");}

    return 0;
}