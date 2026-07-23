#include <stdio.h>

int main() {
    int n, code, qty, i;
    double price, total = 0.0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d", &code, &qty);

        if(code == 1001){
            price = 1.50;
        }
            
        else if(code == 1002){
            price = 2.50;
        }
            
        else if(code == 1003){
            price = 3.50;
        }
            
        else if(code == 1004){
            price = 4.50;
        }
            
        else
            price = 5.50;

        total = total + (price * qty);
    }

    printf("%.2f\n", total);

    return 0;
}
