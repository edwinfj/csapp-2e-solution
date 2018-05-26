#include <stdio.h>

unsigned rotate_left(unsigned x, int n) {
	int nn = (sizeof(x) << 3) - n;
	return (x << n) ^ (x >> 1 >> (nn - 1));

}

int main()
{
	unsigned x;
	int n;
	scanf("%x %d", &x, &n);	
	printf("%x, %d\n", x, n);
	printf("0x%x\n", rotate_left(x, n));

	return 0;
}
