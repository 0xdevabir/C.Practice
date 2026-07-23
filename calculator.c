#include<stdio.h>
#include<math.h>
int sum(float A, float B){
    float sum = A+B;
    return sum;
}
int substraction(float A, float B){
    float substraction = A-B;
    return substraction;
}
int multiplication(float A, float B){
    float multiplication = A*B;
    return multiplication;
}
int divisor(float A, float B){
    float divisor = A/B;
    return divisor;
}
int average(float A, float B){
   float average = (A+B)/2;
   return average;
}
int max(float A, float B){
    int max = 0;
   if(A>B){max=A;}
   else{max=B;}
   return max;
}
int main(){
    float A, B;
    char operation;

    for(int i=0;i<=50;i++){printf("-");}printf("\n");
    printf("For Summation type:   +\nFor Substraction type:   -\nFor multiplication type:   *\nFor devision type:   /\n");
    printf("For average:   a\nFor maximum number:   m");
    for(int i=0;i<=50;i++){printf("-");}printf("\n");
    printf("Type the operation as mention: ");
    scanf("%c", &operation);

    printf("Enter first number: ");
    scanf("%f", &A);
    
    printf("Enter second number: ");
    scanf("%f", &B);

    if(operation=='+')
        {float sumAns = sum(A, B); printf("Sum is = %.2f", sumAns);}
    if(operation=='-')
        {float substractionAns = substraction(A, B); printf("Substraction is = %.2f", substractionAns);}
    if(operation=='*')
        {float multiplicationAns = multiplication(A, B); printf("Multiplication is = %.2f", multiplicationAns);}
    if(operation=='/')
        {float divisorAns = divisor(A, B); printf("Divisor is = %.2f", divisorAns);}
    if(operation=='a')
        {float averageAns = average(A, B); printf("Average is = %.2f", averageAns);}
    if(operation=='m')
        {float maxAns = max(A, B); printf("Max num is = %.2f", maxAns);}
    


    return 0;
}

