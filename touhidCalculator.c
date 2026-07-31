#include<stdio.h>


int sum(int a, int b){

}
int minus(int a, int b){

}
int multiply(int a, int b){

}


int division(int a, int b){
    float division = a/b;
    return division;
}


int main(){
    char op;
    scanf("%c", &op);
    int a, b;
    scanf("%d %d", &a, &b);


    if(op=='+'){
        int sumAns = sum(a, b);
    }

    if(op=='-'){
        int minusAns = minus(a,b);
    }

    if(op=='*'){
        int multiplyAns = multiply(a,b);
    }

    if(op=='/'){
        float divisionAns = division(a,b);
    }



    

    return 0;
}