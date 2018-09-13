#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;

static char *ptr = NULL;
static int time_out = -1;

typedef struct {
	char *s;
	int size;
	FILE *stream;
} Args;


void* thread_sleep(void *varg)
{
	sleep(5);
	sem_wait(&mutex);
	time_out = 1;
	sem_post(&mutex);

	return NULL;
}

void* thread_read(void *varg)
{
	char *p = fgets(((Args*)varg)->s, ((Args*)varg)->size, ((Args*)varg)->stream);
	sem_wait(&mutex);
	ptr = p;
	time_out = 0;
	sem_post(&mutex);

	return NULL;
}

char *tfgets(char *s, int size, FILE *stream)
{
	pthread_t tidr, tids; 
	Args a = {s, size, stream};

	sem_init(&mutex, 0, 1);

	pthread_create(&tidr, NULL, thread_read, &a);
	pthread_create(&tids, NULL, thread_sleep, NULL);

	while (time_out == -1);

	sem_wait(&mutex);
	if (time_out == 0) {
		pthread_cancel(tids);
	} else {
		pthread_cancel(tidr);
	}
	sem_post(&mutex);

	return ptr;
}