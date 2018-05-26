#include <stdio.h>

int mul3div4(int x) {
	int smask = 1 << ((sizeof(int) << 3) - 1);
	int delta = 0;
	!(x & smask) && (delta = 3);
	return x - ((x + delta) >> 2);
}

int main()
{
	int x;
	scanf("%d", &x);
	printf("%d\n", mul3div4(x));

	return 0;
}
