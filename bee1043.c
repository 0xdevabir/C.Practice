#include <stdio.h>
 
int main() {
 
    double A, B, C, Perimetro, Area;
    scanf("%lf %lf %lf", &A, &B, &C);
    
    if(A+B > C && B+C > A && A+C > B){
        Perimetro = A+B+C;
        printf("Perimetro = %.1lf\n", Perimetro);
    }else{
        Area = ((A+B)*C)/2;
        printf("Area = %.1lf\n", Area);
    }
 
    return 0;
}