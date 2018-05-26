#include <stdio.h>

unsigned rep(int j, int k) {
	unsigned x = ~(0 - (1 << (k + j)));
	return x ^ (x >> k);
}

int main()
{
	int j, k;
	scanf("%d %d", &j, &k);
	printf("0x%x\n", rep(j, k));

	return 0;
}
