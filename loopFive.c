#include <stdio.h>

int main() {
    // int number;


    // printf("Give any number: ");
    // scanf("%d", &number);

    // for (int i = 1; i <= 10; i++) {
    //     printf("%d x %d = %d\n", number, i, number * i);
    // }

    int number;
    printf("Give any number: ");
    scanf("%d",&number);
    for(int i = 1; i<=10;i++){
        printf("%d x %d = %d\n", number,i,number*i);
    }

    return 0;
}