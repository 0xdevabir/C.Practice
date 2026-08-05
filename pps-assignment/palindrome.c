#include <stdio.h>

int main(){

    char s[100];
    int n = 0, ok = 1;

    printf("Enter a string: ");
    scanf("%s", s);

    while(s[n] != '\0'){
        n++;
    }

    for(int i = 0; i < n/2; i++){
        if(s[i] != s[n-1-i]){
            ok = 0;
            break;
        }
    }

    if(ok == 1){
        printf("Palindrome\n");
    }else{
        printf("Not palindrome\n");
    }

    return 0;
}
