#include <stdio.h>

int lower_one_mask(int n) {
	return ~(0 - (1 << 1 << (n - 1)));
}

int main()
{
	int x;

	scanf("%d", &x);
	printf("%x\n", lower_one_mask(x));

	return 0;
}
