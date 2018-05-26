#include <stdio.h>
#include <limits.h>
#include <assert.h>

int saturating_add(int x, int y) {
	int smask = INT_MIN;
	int sum = x + y;
	int pos_overflow = !(x & smask) && !(y & smask)\
						&& (sum & smask);
	int neg_overflow = (x & smask) && (y & smask)\
					   && !(sum & smask);

	(pos_overflow && (sum = INT_MAX)); 
	(neg_overflow && (sum = INT_MIN));

	return sum;
}

int main()
{
	int x, y;
	scanf("%x %x", &x, &y);
	printf("0x%x\n", saturating_add(x, y));

	return 0;
}
