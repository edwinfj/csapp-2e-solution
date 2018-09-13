#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned hex, b1, b2, b3, b4;

	sscanf(argv[1], "%u.%u.%u.%u", &b1, &b2, &b3, &b4);
	hex = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;

	printf("0x%x\n", hex);

	return 0;
}
