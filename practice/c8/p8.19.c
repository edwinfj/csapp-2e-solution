#include "csapp.h"
#include <stdlib.h>
#include <error.h>

void sig_handler(int signum)
{
	pid_t pid;

	while ((pid = waitpid(-1, NULL, 0)) > 0)
		printf("reaped one child %d", pid);

	if (errno != ECHILD)
		unix_error("process reap error\n");

	return;
}

void foo(int n)
{
	int i;

	for (i = 0; i < n; ++i)
		Fork();
	printf("hello\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	Signal(SIGCHLD, sig_handler);

	foo(atoi(argv[1]));

	return 0;
}
