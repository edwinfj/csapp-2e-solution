#include <stdio.h>

int tsub_ok(int x, int y) {
	int smask = (1 << ((sizeof(int) << 3) - 1));
	int diff = x - y;
	return !(((x & smask) != (y & smask)) && ((x & smask) != (diff & smask)));
}

