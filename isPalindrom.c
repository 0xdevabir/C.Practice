#include <stdio.h>

int main() {
    long long n, orig, rev = 0;
    int digit;

    if (scanf("%lld", &n) != 1) return 0;

    if (n < 0) {
        printf("Not a palindrome\n");
        return 0;
    }

    orig = n;
    while (n > 0) {
        digit = n % 10;
        rev = rev * 10 + digit;
        n /= 10;
    }

    if (rev == orig)
        printf("Palindrome\n");
    else
        printf("Not a palindrome\n");

    return 0;
}