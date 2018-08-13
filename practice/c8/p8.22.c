#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void unit_error(const char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}


void ret_handler(int signum)
{
}

pid_t Fork(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		unit_error("Fork error");

	return pid;
}
		

int mysystem(char *command)
{
	pid_t pid;
	int status;

	if ((pid = Fork()) == 0) {
		if (execl("/bin/sh", "sh", "-c", command, (char *)NULL) < 0) {
			unit_error("execl error");
			exit(0);
		}
		printf("this line should never be printed\n");
	} 
	
	if (waitpid(pid, &status, 0) < 0) {
		unit_error("waitpid error");
		exit(1);
	}

	if (WIFEXITED(status)) {
		printf("pid returned normally\n");
		return WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status)) {
		printf("pid return abnormally\n");
		return WTERMSIG(status);
	}
}
	

int main(int argc, char *argv[])
{
	int ret;
	ret = mysystem(argv[1]);
	printf("%d\n", ret);

	return ret;
}
