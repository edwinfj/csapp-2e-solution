#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void unit_error(const char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

typedef void (*handler_t)(int);
handler_t Signal(int signum, handler_t *handler)
{
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
	
	if (waitpid(pid, &status, 0) < 0)
		unit_error("waitpid error");

	if (WIFEXITED(status)) {
		printf("pid returned normally\n");
		return WEXITSTATUS(status);
	}
	else {
		printf("pid return abnormally\n");
		return WEXITSTATUS(status);
	}
}
	

int main(int argc, char *argv[])
{
	int ret;
	ret = mysystem(argv[1]);
	printf("%d\n", ret);

	return ret;
}
