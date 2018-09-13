#include "csapp.h"

void *thread(void *vargp)
{
	int tid = (int)vargp;

	printf("Hello, world %d\n", tid);
	return NULL;
}


int main(int argc, char *argv[])
{
	int n = atoi(argv[1]), i;
	pthread_t tid;

	for (i = 0; i < n; ++i)
		Pthread_create(&tid, NULL, thread, (void*)i);

	pthread_exit(NULL);
}
