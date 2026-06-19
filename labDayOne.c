#include<stdio.h>
int main(){

    // printf("Name: MD ABIR HOSSAIN \n");
    // printf("Email: devabir.me@gmail.com \n");
    // printf("CGPA: 3.31");

    float a, b, sum, multiply, divide;

    printf("Input first number: ");
    scanf("%f", &a);
    printf("Input second number: ");
    scanf("%f", &b);

    sum = a+b;
    multiply = a*b;
    divide = a/b;


    

    printf("Sum of that two number is %.2f \n", sum);
    printf("Multiply of that two number is %.2f \n", multiply);
    printf("Divide of that two number is %.2f \n", divide);

    return 0;
};