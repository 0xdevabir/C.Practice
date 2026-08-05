#include <stdio.h>

int main(){

    char s[100];
    int i = 0;

    printf("Enter a string: ");
    scanf("%s", s);

    while(s[i] != '\0'){
        i++;
    }

    printf("Reverse: ");
    for(int j = i-1; j >= 0; j--){
        printf("%c", s[j]);
    }
    printf("\n");

    return 0;
}
