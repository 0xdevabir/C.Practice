#include <stdio.h>

int main() {
	double a, b;

	scanf("%lf %lf", &a, &b);

	printf("MEDIA = %.5f\n", (a * 3.5 + b * 7.5) / 11.0);

	return 0;
}
