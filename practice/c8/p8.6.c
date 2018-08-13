#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	int i;

	printf("Command line arguments:\n");
	for (i = 0; argv[i] != NULL; ++i)
		printf("argv[%d]: %s\n", i, argv[i]);
	printf("\n");

	printf("Environment variables via envp:\n");
	for (i = 0; argv[i] != NULL; ++i)
		printf("envp[%d]: %s\n", i, envp[i]);
	printf("\n");

	printf("Environment variables via __environ:\n");
	for (i = 0; __environ[i] != NULL; ++i)
		printf("__environ[%d]: %s\n", i, __environ[i]);
	printf("\n");
}
