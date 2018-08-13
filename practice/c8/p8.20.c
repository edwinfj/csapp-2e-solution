#include <unistd.h>
#include <stdio.h>

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

	execve(exec_file, argv, environ);

	return 0;
}
