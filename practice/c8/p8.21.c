#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	if (fork() == 0) {
		printf("a");
		exit(0);
	}
	else {
		printf("b");
		waitpid(-1, NULL, 0);
	}
	printf("c");
	exit(0);
}
