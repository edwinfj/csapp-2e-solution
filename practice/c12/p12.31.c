#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <errno.h>

sem_t mutex;
jmp_buf env;

void sigchld_handler(int sig)
{
	int status;
	pid_t pid;

	while((pid = wait(&status)) != -1)
		printf("reeped pid %d\n", pid);
			
	if (errno != ECHILD) {
		printf("error wait\n");
		exit(1);
	}
	longjmp(env, 3);
}

char *tfgets(char *s, int size, FILE *stream)
{
	int val;
	char *ret;
	pid_t pid;

	sem_init(&mutex, 0, 1);
	signal(SIGCHLD, sigchld_handler);
	sem_wait(&mutex);
	val = setjmp(env);

	if (val == 0) {
		if ((pid = fork()) == 0) {
			sleep(5);
			exit(0);
		}
		ret = fgets(s, size, stream);
		// signal(SIGCHLD, SIG_IGN);
		sem_post(&mutex);
	} else {
		sem_post(&mutex);
		printf("long jump branch\n");
		ret = NULL;
	}

	return ret;
}
