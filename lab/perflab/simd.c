#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int data_t; 

#define VBYTES 32
#define OP +
#define IDENT 0
#define VSIZE VBYTES/sizeof(data_t)
#define LEN 1099999
#define INIT 1
#define LOOP 1000

typedef data_t vec_t __attribute__ ((vector_size(VBYTES)));

typedef struct {
  data_t *start;
  int length;
} vec_ptr;

data_t* get_vec_start(vec_ptr p)
{
  return p.start;
}

int vec_length(vec_ptr p)
{
  return p.length;
}

void simd_v1_combine(vec_ptr v, data_t *dest)
{
  long i;
  vec_t accum;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  for (i = 0; i < VSIZE; ++i)
  	accum[i] = IDENT;

  while ((((size_t) data) % VBYTES) && cnt) {
    result = result OP *data++;
	--cnt;
  }

  while (cnt >= VSIZE) {
    vec_t chunk = *((vec_t *) data);
	accum = accum OP chunk;
	data += VSIZE;
    cnt -= VSIZE;
  }

  while (cnt) {
    result = result OP *data++;
	--cnt;
  }

  for (i = 0; i < VSIZE; ++i)
    result = result OP accum[i];

  *dest = result;
}

void init(vec_ptr v)
{
  long i;
  vec_t accum;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);

  for (i = 0; i < VSIZE; ++i)
    accum[i] = INIT;

  while ((((size_t) data) % VBYTES) && cnt) {
    *data++ = INIT;
	--cnt;
  }

  while (cnt >= VSIZE) {
    *((vec_t *) data) = accum;
	data += VSIZE;
	cnt -= VSIZE;
  }

  while (cnt) {
    *data++ = INIT;
	--cnt;
  }
}

int main()
{
  vec_ptr v;
  data_t result;
  long i;
  clock_t t;
  v.length = LEN;
  v.start = (data_t*)malloc(sizeof(data_t) * v.length);

  if (!v.start) {
    printf("Error: failed to alloc memory\n");
	return 1;
  }

  init(v);
  t = clock();
  for(i = 0; i < LOOP; ++i) 
    simd_v1_combine(v, &result);
  t = clock() - t;

  printf("%ld cycles\t%.2f ms\n", t, \
         ((double)t * 1000)/CLOCKS_PER_SEC);
  printf("result %ld\n", result);
}
