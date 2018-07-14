#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

// use LRU to evict lines

#define MAXPATHLEN 1024
#define INPUTLINELEN 128

#define MIN(a, b) ((a) > (b) ? (b) : (a))


typedef struct {
	long tstamp;
	int tag;
	int v;
} Line;

typedef struct {
	Line *lines;
} Set;

typedef struct {
	Set *sets;
	int S;
	int E; // number of lines
} L1cache;


void processCmd(int argc, char *argv[], \
	int *s, int *E, int *b, char *tfile, int *h, int *v)
{

}


void printUsage()
{

}

int main(int argc, char *argv[])
{
	int s, E, b, h, v;
	char tfile[MAXPATHLEN], inputline[INPUTLINELEN];
	L1cache cache;

	processCmd(argc, argv, &s, &E, &b, tfile, &h, &v);

	if (h) {
		printUsage();
		return 0;
	}

	cache.S = 1 << s;
	cache.sets = (Set *)malloc(sizeof(Set) * cache.S);
	if (!cache.sets) {
		printf("Failed to alloc memory for sets\n");
		return 1;
	}

	// TODO: allocate space for cache

	File *f = fopen(tfile, "r");

	while () {
		// TODO: process each line
		
	}

  printSummary(0, 0, 0);
  return 0;
}
