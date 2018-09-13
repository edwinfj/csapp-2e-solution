#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

char *tfgets(char *s, int size, FILE *stream)
{
	fd_set read_set, ready_set;
	struct timeval timer;

	FD_ZERO(&read_set);
	FD_SET(STDIN_FILENO, &read_set);
	timer.tv_sec = 5;
	timer.tv_usec = 0;

	ready_set = read_set;
	select(STDIN_FILENO + 1, &ready_set, NULL, NULL, &timer);
	if (FD_ISSET(STDIN_FILENO, &ready_set))
		return fgets(s, size, stream);
	else
		return NULL;
}