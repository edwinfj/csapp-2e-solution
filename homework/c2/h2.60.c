#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
	return (x & ~(0xff << (i * 8))) ^ (b << (i * 8));
}

int main()
{
	printf("0x%x\n", replace_byte(0x12345678, 2, 0));

	return 0;
}
