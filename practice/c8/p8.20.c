#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	char exec_file[] = "/bin/ls";
	int i;

	printf("environ:\n");
	for (i = 0; environ[i]; ++i)
		printf("%s\n", environ[i]);

	printf("envp:\n");
	for (i = 0; envp[i]; ++i)
		printf("%s\n", envp[i]);

	if (execve(exec_file, argv, environ) == -1) {
		fprintf(stderr, "execve error: %s\n", strerror(errno));
		exit(1);
	}

	return 0;
}
