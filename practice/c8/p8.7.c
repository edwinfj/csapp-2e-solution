#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "csapp.h"

/*
 * the difference from p8.5.c is that p8.5 uses default handler
 * which terminates the calling process immediately.
 * With custom handler, the remaining code of the calling process will be
 * executed.
 */
void sigint_handler(int sig)
{
}

unsigned snooze(unsigned secs)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		unix_error("signal error");

	unsigned left = sleep(secs);
	printf("Slept for %d of %d secs.\t", secs - left, secs);

	if (left)
		printf("User hits ctrl-c after %d secs.\n", secs - left);

	return left;
}

int main(int argc, char *argv[])
{
	snooze(atoi(argv[1]));

	return 0;
}
