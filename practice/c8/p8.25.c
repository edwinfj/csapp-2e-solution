#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>

#define MAXLINE 256
jmp_buf buf;

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

typedef void (*handler_t)(int);
void ret_handler(int signum)
{
	while(waitpid(-1, NULL, 0) > 0);

	if (errno != ECHILD)
		unix_error("waitpid error");

	longjmp(buf, 1);
}

char * tfgets(char *str, int num, FILE *stream)
{
	char *ret = NULL;
	int rc;

	signal(SIGCHLD, ret_handler);
	rc = setjmp(buf);

	if (rc == 0) {
		if (Fork() == 0) {
			sleep(5);
			exit(0);
		}
		ret = fgets(str, num, stream);
		return ret;
	}
	else {
		return NULL;
	}
}

int main()
{
	char str[MAXLINE];
	char *ret;
	ret = tfgets(str, MAXLINE, stdin);
	if (ret)
		printf("%s", str);

	return 0;
}
