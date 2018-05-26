#include <stdio.h>

int divide_power2(int x, int k) {
	int smask = 1 << ((sizeof(int) << 3) - 1);
	int quotient;
	!(smask & x) && (quotient = x >> k);
	(smask & x) && (quotient = (x + (1 << k) - 1) >> k);

	return quotient;
}

int main()
{
	int x, k;
	scanf("%d %d", &x, &k);
	printf("%d\n", divide_power2(x, k));

	return 0;
}
