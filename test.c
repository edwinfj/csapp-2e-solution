/* $begin show-bytes */
#include <stdio.h>
/* $end show-bytes */
#include <stdlib.h>
#include <string.h>
/* $begin show-bytes */

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
	printf(" %.2x", start[i]);    //line:data:show_bytes_printf
    printf("\n");
}

int main()
{
	int a = 0xabcdefff;
	unsigned b = 0xfeabdcaa;
	long long c = b;
	long long e = a;
	unsigned long long d = a;
	show_bytes((byte_pointer)&c, sizeof(c));
	show_bytes((byte_pointer)&d, sizeof(d));
    show_bytes((byte_pointer)&e, sizeof(e)); 
	return 0;
}
