#include <stdio.h>

int xbyte(unsigned word, int bytenum) {
	int offset = (sizeof(word) - bytenum - 1) << 3;
	int size = sizeof(word) << 3;
	return (int)(word << offset) >> (size - 8);
}

int main()
{
	unsigned w;
	int b;

	scanf("%x %d", &w, &b);
	printf("0x%x\n", xbyte(w, b));

	return 0;
}
