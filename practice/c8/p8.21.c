#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	if (fork() == 0) {
		printf("a");
		fflush(stdout);
		exit(0);
	}
	else {
		printf("b");
		fflush(stdout);
		waitpid(-1, NULL, 0);
	}
	printf("c");
	exit(0);
}
