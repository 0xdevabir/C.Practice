#include <math.h>
#include <stdio.h>

float add(float a, float b)
{
  return a + b;
}

float subtract(float a, float b)
{
  return a - b;
}

float multiply(float a, float b)
{
  return a * b;
}

float divide(float a, float b)
{
  return a / b;
}

float remainderValue(float a, float b)
{
  return (int)a % (int)b;
}

float percentage(float a, float b)
{
  return (a / 100.0f) * b;
}

float absolute(float a)
{
  return fabs(a);
}

float square(float a)
{
  return a * a;
}

float cube(float a)
{
  return a * a * a;
}

float average(float a, float b)
{
  return (a + b) / 2.0f;
}

float bigger(float a, float b)
{
  return a > b ? a : b;
}

float smaller(float a, float b)
{
  return a < b ? a : b;
}

int main()
{
  float firstNumber, secondNumber;
  char operation;

  printf("\n==============================\n");
  printf("      Simple Calculator\n");
  printf("==============================\n\n");

  printf("What do you want to do?\n");
  printf(" +  Add\n");
  printf(" -  Subtract\n");
  printf(" *  Multiply\n");
  printf(" /  Divide\n");
  printf(" %%  Remainder\n");
  printf(" p  Percentage\n");
  printf(" a  Absolute value\n");
  printf(" s  Square\n");
  printf(" c  Cube\n");
  printf(" m  Maximum\n");
  printf(" n  Minimum\n");
  printf(" v  Average\n\n");

  printf("Enter your operation: ");
  scanf(" %c", &operation);

  printf("Enter first number: ");
  scanf("%f", &firstNumber);

  if (operation == 'a' || operation == 's' || operation == 'c') {
    secondNumber = 0;
  } else {
    printf("Enter second number: ");
    scanf("%f", &secondNumber);
  }

  printf("\n------------------------------\n");

  if (operation == '+') {
    printf("Result: %.2f\n", add(firstNumber, secondNumber));
  } else if (operation == '-') {
    printf("Result: %.2f\n", subtract(firstNumber, secondNumber));
  } else if (operation == '*') {
    printf("Result: %.2f\n", multiply(firstNumber, secondNumber));
  } else if (operation == '/') {
    printf("Result: %.2f\n", divide(firstNumber, secondNumber));
  } else if (operation == '%') {
    printf("Result: %.0f\n", remainderValue(firstNumber, secondNumber));
  } else if (operation == 'p') {
    printf("Result: %.2f\n", percentage(firstNumber, secondNumber));
  } else if (operation == 'a') {
    printf("Result: %.2f\n", absolute(firstNumber));
  } else if (operation == 's') {
    printf("Result: %.2f\n", square(firstNumber));
  } else if (operation == 'c') {
    printf("Result: %.2f\n", cube(firstNumber));
  } else if (operation == 'm') {
    printf("Result: %.2f\n", bigger(firstNumber, secondNumber));
  } else if (operation == 'n') {
    printf("Result: %.2f\n", smaller(firstNumber, secondNumber));
  } else if (operation == 'v') {
    printf("Result: %.2f\n", average(firstNumber, secondNumber));
  } else {
    printf("Sorry, that operation is not available.\n");
  }

  printf("------------------------------\n");

  return 0;
}
