#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// use LRU to evict lines

#define MAXPATHLEN 1024
#define INPUTLINELEN 128

#if defined(__x86_64) || defined(__x86_64__)
#define ADDR_LEN 64
#else
#define ADDR_LEN 32
#endif

#define MIN(a, b) ((a) > (b) ? (b) : (a))


typedef struct {
	unsigned long tstamp;
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


enum OPTYPE { L, S, M };

void processCmd(int argc, char *argv[], \
	int *s, int *E, int *b, char *tfile, int *h, int *v)
{
	int len, i, j;
	
	for (i = 1; i < argc; ++i) {
		len = strlen(argv[i]);
		if (argv[i][0] == '-') {
			for (j = 1; j < len; ++j) {
				switch (argv[i][j]) {
					case 'h':
						*h = 1;
						return;
					case 'v':
						*v = 1;
						break;
					case 's':
						*s =(int)strtol(argv[++i], NULL, 10);
						break;
					case 'E':
						*E = (int)strtol(argv[++i], NULL, 10);
						break;
					case 'b':
						*b = (int)strtol(argv[++i], NULL, 10);
						break;
					case 't':
						sprintf(tfile, "%s", argv[++i]);
						break;
					default:
						printf("Usage error\n");
						exit(1);
				}
			}
		} else {
			printf("Usage error\n");
			exit(1);
		}
	}
}


void printUsage()
{
	printf("Usage: [-hv] -s <num> -E <num> -b <num> -t <file>\n");
}


void preprocessOps(const char *il, int s, int b, int *op, \
					unsigned long *set, unsigned long *tag)
{
	char c;
	unsigned long addr;
	unsigned long set_m = (1 << s) - 1;
	sscanf(il, " %c %lx,", &c, &addr);
	switch (c) {
	case 'L': *op = L; break;
	case 'S': *op = S; break;
	case 'M': *op = M; break;
	default:;
	}
	*set = (addr >> b) & set_m;
	*tag = (addr >> b) >> s;
}


void cacheOps(L1cache *p, const int op, const unsigned long set,\
				 const unsigned long tag, const unsigned long counter, \
				 int *h, int *m, int *ev)
{
	// check if hit
	// assume the counter never overflow
	int Lh = 0, Sh = 0, miss = 0, evict = 0, i, lru = -1, emptyLidx = -1;
	
	Set *pSet = &(p->sets[set]);
	for (i = 0; i < p->E && !(Lh || Sh); ++i) {
		Line *pLine = &(pSet->lines[i]);
		if (pLine->v == 1) {
			if (pLine->tag == tag) { // hit
				if (op == S)
					Sh = 1;
				else
					Lh = 1;
				pLine->tstamp = counter;
			} else { // valid but tag mismatch
				if (lru == -1 || \
				pSet->lines[lru].tstamp > pSet->lines[i].tstamp)
					lru = i;
			}
		} else if (emptyLidx == -1) { // invalid line
			emptyLidx = i;
		}
	}
	
	if (!(Lh || Sh)) { // miss
		miss = 1;
		if (emptyLidx == -1) { // no empty line, evict
			evict = 1;
			pSet->lines[lru].tag = tag;
			pSet->lines[lru].v = 1;
			pSet->lines[lru].tstamp = counter;
		} else { // has empty line
			pSet->lines[emptyLidx].tag = tag;
			pSet->lines[emptyLidx].v = 1;
			pSet->lines[emptyLidx].tstamp = counter;
		}
	}
	
	if (op == M)
		Sh = 1;
	
	*h = Lh + Sh;
	*m = miss;
	*ev = evict;
}


int main(int argc, char *argv[])
{
	int s, E, b, h = 0, v = 0, hits = 0, misses = 0, evictions = 0;
	int i, j, k, len;
	int op;
	unsigned long tag, set, counter = 0;
	char tfile[MAXPATHLEN], inputline[INPUTLINELEN];
	L1cache cache;

	processCmd(argc, argv, &s, &E, &b, tfile, &h, &v);
#if 0
	printf("s - %d, E - %d, b - %d, h - %d, v - %d, trace - %s\n",\
			s, E, b, h, v, tfile);
#endif

	if (h) {
		printUsage();
		return 0;
	}

	cache.S = 1 << s;
	cache.E = E;
	cache.sets = (Set *)malloc(sizeof(Set) * cache.S);
	if (!cache.sets) {
		printf("Failed to alloc memory for sets\n");
		return 1;
	}

	for (i = 0; i < cache.S; ++i) {
		cache.sets[i].lines = (Line *)calloc(cache.E, sizeof(Line));
		if (!cache.sets[i].lines) {
			printf("Failed to allocate memory for lines\n");
			return 1;
		}
	}

	FILE *f = fopen(tfile, "r");

	counter = 0;
	while (fgets(inputline, INPUTLINELEN - 1, f)) {
		if (inputline[0] == 'I')
			continue;
		// process each valid line
		preprocessOps(inputline, s, b, &op, &set, &tag);
#if 0
		printf("op %d, set %lx, tag %lx\n", op, set, tag);
#endif
		cacheOps(&cache, op, set, tag, counter, &i, &j, &k);
		++counter;
		
		hits += i;
		misses += j;
		evictions += k;
		if (v) {
			len = strlen(inputline);
			if (inputline[len - 1] == '\n')
				inputline[len - 1] = '\0';
			if (j) { // first miss
				strcat(inputline, " miss");
				if (k)
					strcat(inputline, " eviction");
			} else {
				strcat(inputline, " hit");
			}
			if (op == M)
				strcat(inputline, " hit");
			printf("%s\n", inputline + 1);
		}
	}
	
	fclose(f);

	for (i = 0; i < cache.S; ++i) {
		free(cache.sets[i].lines);
	}
	free(cache.sets);

	printSummary(hits, misses, evictions);
	return 0;
}
