#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef float data_t; 

#define VBYTES 32
#define OP *
#define IDENT 1
#define VSIZE VBYTES/sizeof(data_t)
#define LEN 300000000
#define INIT 1
#define LOOP 10

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
    result = result OP (*data++);
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


void simd_v2_combine(vec_ptr v, data_t *dest)
{
  long i;
  vec_t accum0, accum1, accum2, accum3;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  // initialize accumulators
  for (i = 0; i < VSIZE; ++i) {
    accum0[i] = IDENT;
    accum1[i] = IDENT;
    accum2[i] = IDENT;
    accum3[i] = IDENT;
  }

  // align address
  while ((((size_t) data) % VBYTES) && cnt) {
    result = result OP (*data++);
    --cnt;
  }

  // combine
  while (cnt >= (4 * VSIZE)) {
    vec_t vec0 = *((vec_t *)data);
    vec_t vec1 = *((vec_t *)(data + VSIZE));
    vec_t vec2 = *((vec_t *)(data + 2 * VSIZE));
    vec_t vec3 = *((vec_t *)(data + 3 * VSIZE));
    accum0 = accum0 OP vec0;
    accum1 = accum1 OP vec1;
    accum2 = accum2 OP vec2;
    accum3 = accum3 OP vec3;
    data += 4 * VSIZE;
    cnt -= 4 * VSIZE;
  }

  // combine the rest
  while (cnt) {
    result = result OP (*data++);
    --cnt;
  }

  // combine the accumulators
  accum0 = (accum0 OP accum1) OP (accum2 OP accum3);
  for (i = 0; i < VSIZE; ++i) {
    result = result OP accum0[i];
  }

  *dest = result;
}


void simd_v3_combine(vec_ptr v, data_t *dest)
{
  long i;
  vec_t accum0;
  data_t *data = get_vec_start(v);
  int cnt = vec_length(v);
  data_t result = IDENT;

  // initialize accumulators
  for (i = 0; i < VSIZE; ++i) {
    accum0[i] = IDENT;
  }

  // align address
  while ((((size_t) data) % VBYTES) && cnt) {
    result = result OP (*data++);
    --cnt;
  }

  // combine
  while (cnt >= (4 * VSIZE)) {
    vec_t vec0 = (*((vec_t *)data));
    vec_t vec1 = *((vec_t *)(data + VSIZE));
    vec_t vec2 = *((vec_t *)(data + 2 * VSIZE));
    vec_t vec3 = *((vec_t *)(data + 3 * VSIZE));
    accum0 = accum0 OP ((vec0 OP vec1) OP (vec2 OP vec3));
    data += 4 * VSIZE;
    cnt -= 4 * VSIZE;
  }

  // combine the rest
  while (cnt) {
    result = result OP (*data++);
    --cnt;
  }

  // combine the accumulators
  for (i = 0; i < VSIZE; ++i) {
    result = result OP accum0[i];
  }

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
    *(data++) = INIT;
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
  printf("result %f\n", result);

  t = clock();
  for(i = 0; i < LOOP; ++i) 
    simd_v3_combine(v, &result);
  t = clock() - t;
  printf("%ld cycles\t%.2f ms\n", t, \
         ((double)t * 1000)/CLOCKS_PER_SEC);
  printf("result %f\n", result);
}
