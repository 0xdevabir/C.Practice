#include<stdio.h> 
int main(){

    int totalBill;

    printf("Total bill is: ");
    scanf("%d", &totalBill);

    if(totalBill <= 999){
        printf("Kono dicount paba na tumiiiii, ebar %d tk deu\n", totalBill);
    }
    else if(totalBill < 5000){
        totalBill = totalBill - (totalBill * 0.1); 
        printf("Discount peyecho tumiiii, ebar %d tk deu\n", totalBill);
    }
    else{
        totalBill = totalBill - (totalBill * 0.15);
        printf("Discount peyecho tumiiii, ebar %d tk deu\n", totalBill);
    }



    
    return 0;




}