#include <stdio.h>

int main(){

    int a[100], n, sum = 0;

    printf("How many numbers: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++){
        sum = sum + a[i];
    }

    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", (float)sum/n);

    return 0;
}
