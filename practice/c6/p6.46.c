#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1111 
#define LEN N*N
#define LIMIT 20
#define LOOP 100
#define min(a, b) ((a) > (b) ? (b) : (a))

void transpose(int *dst, int *src, int dim, int blk)
{
  int bc, br, bcn, brn, i, j;
  
  br = 0;
  do {
	brn = min(blk + br, dim);
	// printf("br %d, brn %d\n", br, brn);
	bc = 0;
	do {
      bcn = min(blk + bc, dim);
      // printf("bc %d, bcn %d\n", bc, bcn);
	  
	  for (i = br; i < brn; ++i) {
	    for (j = bc; j < bcn - 1; j+=2) {
		// it turns out loop unrolling does not help
		  dst[j*dim + i] = src[i*dim + j];
		  dst[(j+1)*dim + i] = src[i*dim + j + 1];
		}
		for (; j < bcn; ++j)
		  dst[j*dim + i] = src[i*dim + j];
      }
	  
	  bc = bcn;
	} while (bc < dim);

	br = brn;
  } while (br < dim);
}


int main()
{
  int *dst = (int*)malloc(sizeof(int) * LEN);
  int *src = (int*)malloc(sizeof(int) * LEN);
  int trials[LIMIT] = {1, 10, 20, 30, 40, 50, 60, 70, 80, 90, \
                       100, 110, 120, 130, 140, 150, 160, 170, 400, N};
  clock_t t;

  if (!dst || !src) {
    printf("Error: failed to allocate memory\n");
	return 1;
  }

  for (int i = 0; i < LIMIT; ++i) {
    t = clock();
    for (int j = 0; j < LOOP; ++j) {
	  transpose(dst, src, N, trials[i]);
	  // when a loop finishes, the cache stores the bottom right of 
	  // the matrices, so loop to loop has no warm up
	}
	t = clock() - t;
	printf("%d blocksize\t%ld clock ticks\t%.2f ms\n", trials[i], t,\
	((double)t*1000)/CLOCKS_PER_SEC);
  }

  free(dst);
  free(src);

  return 0;
}
