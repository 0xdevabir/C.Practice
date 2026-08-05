#include <stdio.h>

int main(){

    int a[100], n, even = 0, odd = 0;

    printf("How many numbers: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++){
        if(a[i] % 2 == 0){
            even++;
        }else{
            odd++;
        }
    }

    printf("Even = %d\n", even);
    printf("Odd = %d\n", odd);

    return 0;
}
