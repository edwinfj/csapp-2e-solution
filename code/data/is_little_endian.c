#include <stdio.h>

int is_little_endian() {
	int x = 0x1234;
	return ((char*)(&x))[0] == 0x34;
}

int main()
{
	printf("%d\n", is_little_endian());

	return 0;
}
