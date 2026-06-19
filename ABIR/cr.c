#include <stdio.h>

int main() {
    int amount, notes, total = 0;

    printf("Enter the amount in Taka: ");
    scanf("%d", &amount);

    printf("\nNotes required:\n");

    if (notes == amount / 1000) { printf("1000 Taka : %d\n", notes); total += notes; amount %= 1000; }
    if (notes == amount / 500)  { printf("500 Taka  : %d\n", notes); total += notes; amount %= 500;  }
    if (notes == amount / 200)  { printf("200 Taka  : %d\n", notes); total += notes; amount %= 200;  }
    if (notes == amount / 100)  { printf("100 Taka  : %d\n", notes); total += notes; amount %= 100;  }
    if (notes == amount / 50)   { printf("50 Taka   : %d\n", notes); total += notes; amount %= 50;   }
    if (notes == amount / 20)   { printf("20 Taka   : %d\n", notes); total += notes; amount %= 20;   }
    if (notes == amount / 10)   { printf("10 Taka   : %d\n", notes); total += notes; amount %= 10;   }
    if (notes == amount / 5)    { printf("5 Taka    : %d\n", notes); total += notes; amount %= 5;    }
    if (notes == amount / 2)    { printf("2 Taka    : %d\n", notes); total += notes; amount %= 2;    }
    if (notes == amount / 1)    { printf("1 Taka    : %d\n", notes); total += notes; amount %= 1;    }

    printf("-------------------\nTotal notes: %d\n", total);
    return 0;
}