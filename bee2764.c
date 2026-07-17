#include <stdio.h>

int main() {
    int day, month, year;

    scanf("%d/%d/%d", &day, &month, &year);

    printf("%02d/%02d/%02d\n", month, day, year);
    printf("%02d/%02d/%02d\n", year, month, day);
    printf("%02d-%02d-%02d\n", day, month, year);

    return 0;
}