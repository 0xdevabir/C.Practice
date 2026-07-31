#include<stdio.h>
#include<math.h>
float sum(float A, float B){
    float sum = A+B;
    return sum;
}
float substraction(float A, float B){
    float substraction = A-B;
    return substraction;
}
float multiplication(float A, float B){
    float multiplication = A*B;
    return multiplication;
}
float divisor(float A, float B){
    float divisor = A/B;
    return divisor;
}
float average(float A, float B){
   float average = (A+B)/2;
   return average;
}
float max(float A, float B){
    float max = 0;
   if(A>B){max=A;}
   else{max=B;}
   return max;
}
float power(float A, float B){
    float power = pow(A, B);
    return power;
}
float squareRoot(float A, float B){
    float squareRoot = sqrt(A);
    return squareRoot;
}
float logarithm(float A, float B){
    float logarithm = log(A);
    return logarithm;
}
float sine(float A, float B){
    float sine = sin(A);
    return sine;
}
float cosine(float A, float B){
    float cosine = cos(A);
    return cosine;
}
float tangent(float A, float B){
    float tangent = tan(A);
    return tangent;
}
int main(){
    float A, B;
    char operation;

    for(int i=0;i<=12;i++){printf("-.-");}printf("\n");
    printf("For Summation type:   +\nFor Substraction type:   -\nFor multiplication type:   *\nFor devision type:   /\n");
    printf("For average:   a\nFor maximum number:   m\nFor power:   p\nFor square root:   r\nFor log:   l\nFor sine:   s\nFor cosine:   c\nFor tangent:   t\n");
    for(int i=0;i<=12;i++){printf("-.-");}printf("\n");
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
    if(operation=='p')
        {float powerAns = power(A, B); printf("Power is = %.2f", powerAns);}
    if(operation=='r')
        {float squareRootAns = squareRoot(A, B); printf("Square Root is = %.2f", squareRootAns);}
    if(operation=='l')
        {float logarithmAns = logarithm(A, B); printf("Log is = %.2f", logarithmAns);}
    if(operation=='s')
        {float sineAns = sine(A, B); printf("Sine is = %.2f", sineAns);}
    if(operation=='c')
        {float cosineAns = cosine(A, B); printf("Cosine is = %.2f", cosineAns);}
    if(operation=='t')
        {float tangentAns = tangent(A, B); printf("Tangent is = %.2f", tangentAns);}
    

    return 0;
}

