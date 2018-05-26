#include <stdio.h>

int main()
{
	int x = 0x89abcdef;
	int y = 0x76543210;
	printf("0x%x\n", (x & 0xff) ^ (y & 0xffffff00));

	return 0;
}
