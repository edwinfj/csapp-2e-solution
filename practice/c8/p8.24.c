#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define N 2
#define MAXLINE 1024

void unix_error(const char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));

	exit(0);
}

pid_t Fork(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		unix_error("fork error");

	return pid;
}
	
int main()
{
	int status, i, sig;
	char msg[MAXLINE];
	pid_t pid;

	for (i = 0; i < N; ++i) {
		if ((pid = Fork()) == 0) {
			// write to read segment
			char *tmp = NULL;
			tmp[0] = 'a';
			exit(0);
		}
	}

	while ((pid = waitpid(-1, &status, 0)) > 0) {
		if (WIFEXITED(status))
			printf("child %d terminated normally with exit status=%d\n",
					pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status)) {
			sig = WTERMSIG(status);
			sprintf(msg, "child %d terminated by signal %d", pid, sig);
			psignal(sig, msg);
		}
		else
			printf("child %d terminated abnormally\n", pid);
	}

	if (errno != ECHILD)
		unix_error("waitpid error");

	exit(0);
}
