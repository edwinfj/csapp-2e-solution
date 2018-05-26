#include <stdio.h>

int fits_bits(int x, int n) {
	int s = sizeof(x) << 3;
	return x == (x << (s-n) >> (s-n)); 
}

int main()
{
	int x, n;
	scanf("%x %d", &x, &n);
	printf("%d\n", fits_bits(x, n));

	return 0;
}
