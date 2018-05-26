#include <stdio.h>

int odd_ones(unsigned x) {
	x = (x >> 16) ^ (x );
	x = (x >> 8) ^ x;
	x = (x >> 4) ^ x;
	x = (x >> 2) ^ x;
	x = (x >> 1) ^ x;
	return x & 0x1;
}

int main()
{
	unsigned x;
	scanf("%u", &x);
	printf("%d\n", odd_ones(x));

	return 0;
}
