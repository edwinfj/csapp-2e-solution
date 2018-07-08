#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define N 1024
#define LEN N*N
#define LIMIT 20
#define LOOP 100

int convert(int *G, int dim, int blk)
{
  int br, brn, bc, bcn, i, j, limit, tmp;
  int count = 0, t;

  br = 0;
  do {
    brn = MIN(br + blk, dim);
	bc = 0;
	do {
	  bcn = MIN(bc + blk, brn);

      for (i = br; i < brn; ++i) {
	    limit = MIN(i, bcn);
	    for (j = bc; j < limit - 1; j += 2) {
		// it turns out loop unrolling does not help
		  tmp = G[i*dim + j] || G[j*dim + i];
		  G[i*dim + j] = tmp;
		  G[j*dim + i] = tmp;
		  t = G[i*dim + j + 1] || G[(j+1)*dim + i];
		  G[i*dim + j + 1] = t;
		  G[(j+1)*dim + i] = t;
		  count += 2;
		}
		for (; j < limit; ++j) {
		  tmp = G[i*dim + j] || G[j*dim + i];
		  G[i*dim + j] = tmp;
		  G[j*dim + i] = tmp;
		  ++count;
		}
	  }

	  bc = bcn;
	} while (bc < brn);

	br = brn;
  } while (br < dim);

  return count;
}


int main()
{
  int *G = (int *)malloc(sizeof(int) * LEN);
  int trials[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,\
                  12, 13, 14, 15, 16, 17, 18, 100, 1024};
  clock_t t;
  int count;

  if (!G) {
    printf("Error: failed to alloc memory\n");
	return 1;
  }

  for (int i = 0; i < LIMIT; ++i) {
    t = clock();
    for (int j = 0; j < LOOP; ++j) {
	  count = convert(G, N, trials[i]);
	}
	t = clock() - t;
	printf("%d block\t%d count\t%.2f ms\n", trials[i], count,\
		((double)t * 1000)/CLOCKS_PER_SEC);
  }

  free(G);
}

