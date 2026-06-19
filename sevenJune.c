#include <stdio.h>

int main() {
    int choice;

    printf("====== Choose a problem to solve ======\n");
    printf("1. Check if a number is positive, negative or zero\n");
    printf("2. Check if two numbers are equal or not\n");
    printf("3. Check if a number is divisible by 3 or not\n");
    printf("4. Check if a character is a number or alphabet\n");
    printf("5. Check if a character is a vowel or consonant\n");
    printf("6. Check if a number is between 50 and 100\n");
    printf("7. Check if a student can sit for exam (attendance >= 75%%)\n");
    printf("Enter your choice (1-7): ");
    scanf("%d", &choice);

    if (choice == 1) {
        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        if (num == 0) {
            printf("The number is zero.\n");
        } else if (num > 0) {
            printf("The number is positive.\n");
        } else {
            printf("The number is negative.\n");
        }
    }
    else if (choice == 2) {
        int num1, num2;
        printf("Enter first number: ");
        scanf("%d", &num1);
        printf("Enter second number: ");
        scanf("%d", &num2);

        if (num1 == num2) {
            printf("Both numbers are equal.\n");
        } else {
            printf("Both numbers are not equal.\n");
        }
    }
    else if (choice == 3) {
        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        if (num % 3 == 0) {
            printf("The number is perfectly divisible by 3.\n");
        } else {
            printf("The number is not divisible by 3.\n");
        }
    }
    else if (choice == 4) {
        char ch;
        printf("Enter a character: ");
        scanf(" %c", &ch);

        if (ch >= '0' && ch <= '9') {
            printf("It is a number.\n");
        } else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            printf("It is an alphabet.\n");
        } else {
            printf("It is neither a number nor an alphabet.\n");
        }
    }
    else if (choice == 5) {
        char ch;
        printf("Enter a character: ");
        scanf(" %c", &ch);

        if (ch >= 'A' && ch <= 'Z') {
            ch = ch + 32;
        }

        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            printf("It is a vowel.\n");
        } else if (ch >= 'a' && ch <= 'z') {
            printf("It is a consonant.\n");
        } else {
            printf("It is not an alphabet.\n");
        }
    }
    else if (choice == 6) {
        int num;
        printf("Enter a number: ");
        scanf("%d", &num);

        if (num >= 50 && num <= 100) {
            printf("The number is between 50 and 100.\n");
        } else {
            printf("The number is not between 50 and 100.\n");
        }
    }
    else if (choice == 7) {
        float attendance;
        printf("Enter attendance percentage: ");
        scanf("%f", &attendance);

        if (attendance >= 75) {
            printf("Student can sit for the exam.\n");
        } else {
            printf("Student cannot sit for the exam.\n");
        }
    }
    else {
        printf("Invalid choice. Please enter a number from 1 to 7.\n");
    }

    return 0;
}
