#include<stdio.h>
int main(){

    double N;
    scanf("%lf", &N);

    printf("NOTAS:\n");
    if(N>=100){
        int Hundred_Note=N/100;
        printf("%d nota(s) de R$ 100.00\n", Hundred_Note);
        N = N-Hundred_Note*100;
    }else{printf("0 nota(s) de R$ 100.00\n");}
    if(N>=50){
        int Fifty_Note=N/50;
        printf("%d nota(s) de R$ 50.00\n", Fifty_Note);
        N = N-Fifty_Note*50;
    }else{printf("0 nota(s) de R$ 50.00\n");}
    if(N>=20){
        int Twenty_Note=N/20;
        printf("%d nota(s) de R$ 20.00\n", Twenty_Note);
        N = N-Twenty_Note*20;
    }else{printf("0 nota(s) de R$ 20.00\n");}
    if(N>=10){
        int Ten_Note=N/10;
        printf("%d nota(s) de R$ 10.00\n", Ten_Note);
        N = N-Ten_Note*10;
    }else{printf("0 nota(s) de R$ 10.00\n");}
    if(N>=5){
        int Five_Note=N/5;
        printf("%d nota(s) de R$ 5.00\n", Five_Note);
        N = N-Five_Note*5;
    }else{printf("0 nota(s) de R$ 5.00\n");}
    if(N>=2){
        int Two_Note=N/2;
        printf("%d nota(s) de R$ 2.00\n", Two_Note);
        N = N-Two_Note*2;
    }else{printf("0 nota(s) de R$ 2.00\n");}

    printf("MOEDAS:\n");

    if(N>=1){
        int One_Coin=N/1;
        printf("%d moeda(s) de R$ 1.00\n", One_Coin);
        N = N-One_Coin*1;
    }else{printf("0 moeda(s) de R$ 1.00\n");}

    if(N>=.50){
        int Half_Coin=N/.50;
        printf("%d moeda(s) de R$ 0.50\n", Half_Coin);
        N = N-Half_Coin*0.50;
    }else{printf("0 moeda(s) de R$ 0.50\n");}

    if(N>=0.25){
        int Twenty_Five_Cent_Coin=N/0.25;
        printf("%d moeda(s) de R$ 0.25\n", Twenty_Five_Cent_Coin);
        N = N-Twenty_Five_Cent_Coin*0.25;
    }else{printf("0 moeda(s) de R$ 0.25\n");}

    if(N>=.10){
        int Ten_Cent_Coin=N/.1;
        printf("%d moeda(s) de R$ 0.10\n", Ten_Cent_Coin);
        N = N-Ten_Cent_Coin*1;
    }else{printf("0 moeda(s) de R$ 0.10\n");}

    if(N>=.05){
        int Five_Cent_Coin=N/0.05;
        printf("%d moeda(s) de R$ 0.05\n", Five_Cent_Coin);
        N = N-Five_Cent_Coin*.5;
    }else{printf("0 moeda(s) de R$ 0.05\n");}


    if(N>=.01){
        int One_Cent_Coin=N/.01;
        printf("%d moeda(s) de R$ 0.01\n", One_Cent_Coin);
        N = N-One_Cent_Coin*.01;
    }else{printf("0 moeda(s) de R$ 0.01\n");}




    return 0;
}

 	
