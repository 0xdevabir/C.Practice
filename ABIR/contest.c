#include <stdio.h>

int main() {
	long long n, m, a;
	long long x, y;

	scanf("%lld %lld %lld", &n, &m, &a);

	x = (n + a - 1) / a;
	y = (m + a - 1) / a;

	printf("%lld\n", x * y);

	return 0;
}
