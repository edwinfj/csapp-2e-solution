#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs)
{
	unsigned left = sleep(secs);

	printf("Slept %d of %d secs.\n", secs - left, secs);

	return left;
}

int main(int argc, char *argv[])
{
	snooze(atoi(argv[1]);

	return 0;
}
