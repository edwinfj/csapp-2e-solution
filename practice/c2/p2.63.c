#include <stdio.h>

unsigned srl(unsigned x, int k) {
	unsigned xsra = (int) x >> k;
	return xsra & ((1 << ((sizeof(unsigned) << 3) - k)) - 1);
}

int sra(int x, int k) {
	int xsrl = (unsigned) x >> k;
	int n = sizeof(unsigned) << 3;
	int mask = (1 << n - 1);
	return xsrl ^ ((0 - ((x & mask) == mask)) << (n - k));
}	

int main()
{
	printf("%d, %d\n", srl(0xffffffff, 8) == 0x00ffffff,\
			sra(0xfe123456, 8) == 0xfffe1234);

	return 0;
}
