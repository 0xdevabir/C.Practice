#include <stdio.h>

int main() {

    double A, B, C;
    scanf("%lf %lf %lf", &A, &B, &C);

    if (A < B) {
        double temp = A;
        A = B;
        B = temp;
    }
    if (A < C) {
        double temp = A;
        A = C;
        C = temp;
    }
    if (B < C) {
        double temp = B;
        B = C;
        C = temp;
    }

    if (A >= B + C) {
        printf("NAO FORMA TRIANGULO\n");
    } else {
        if (A * A == B * B + C * C) {
            printf("TRIANGULO RETANGULO\n");
        } else if (A * A > B * B + C * C) {
            printf("TRIANGULO OBTUSANGULO\n");
        } else {
            printf("TRIANGULO ACUTANGULO\n");
        }

        if (A == B && B == C) {
            printf("TRIANGULO EQUILATERO\n");
        } else if (A == B || A == C || B == C) {
            printf("TRIANGULO ISOSCELES\n");
        }
    }

    return 0;
}

// NOTAS:
// 5 nota(s) de R$ 100.00
// 1 nota(s) de R$ 50.00
// 1 nota(s) de R$ 20.00
// 0 nota(s) de R$ 10.00
// 1 nota(s) de R$ 5.00
// 0 nota(s) de R$ 2.00
// MOEDAS:
// 1 moeda(s) de R$ 1.00
// 1 moeda(s) de R$ 0.50
// 0 moeda(s) de R$ 0.25
// 2 moeda(s) de R$ 0.10
// 0 moeda(s) de R$ 0.05
// 3 moeda(s) de R$ 0.01 