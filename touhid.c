#include<stdio.h>
int main(){
    int n, seatTogether=0, a[999][999];
    scanf("%d", &n);


    for(int i=0;i<n;i++){

        for(int j=0;j<n;j++){
            scanf("%d", &a[i][j]);
        }

    }




    for(int i=0;i<=n;i++){

        for(int j=0;j<=n;j++){

            if(a[i][j]==0){
                if(j<=n-1){
                    if(a[i][j+1]==0){
                        seatTogether=1;
                        break;
                    }
                }
            }
        }
    }


    if(seatTogether==1){
        printf("hello");
    }else{
        printf("hello");
    }
}
