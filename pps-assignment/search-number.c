#include <stdio.h>

int main(){

    int a[100], n, x, pos = -1;

    printf("How many numbers: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    printf("Which number to search: ");
    scanf("%d", &x);

    for(int i = 0; i < n; i++){
        if(a[i] == x){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        printf("Not found\n");
    }else{
        printf("Found at position %d\n", pos+1);
    }

    return 0;
}
