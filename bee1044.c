#include <stdio.h>
 
int main() {
 
    int A, B;
    
    scanf("%d %d", &A, &B);
    
    int ans = B%A;
    
    if(ans==0){printf("Sao Multiplos\n");}
    else{printf("Nao sao Multiplos\n");}
 
    return 0;
}