#include<stdio.h>
int main(){

    int n, total=0, avg, a[999][999];

    scanf("%d", &n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d", &a[i][j]);
            total += a[i][j];
        }
    }

    avg = total/(n*n);

    printf("%d", avg);
    return 0;
}