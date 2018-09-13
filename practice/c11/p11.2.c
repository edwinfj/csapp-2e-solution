#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned hex;
    unsigned char b1, b2, b3, b4;

	sscanf(argv[1], "%x", &hex);

	b1 = (hex & 0xff000000) >> 24;
	b2 = (hex & 0x00ff0000) >> 16;
	b3 = (hex & 0x0000ff00) >> 8;
	b4 = (hex & 0x000000ff);

	printf("%u.%u.%u.%u\n", b1, b2, b3, b4);

	return 0;
}
