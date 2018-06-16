#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	long val = 0;
	unsigned long x;
	int i, ret;
	scanf("%lx", &x);
	for (i = 0; i < 8; i++) {
		val += x & 0x0101010101010101L;
		x >>= 1;
	}
	val += (val >> 32);
	val += (val >> 16);
	val += (val >> 8);
	ret = val & 0xff;
	printf("%d\n", ret);
}
