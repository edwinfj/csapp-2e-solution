/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define BROW	8
#define BSIZE 9
#define BSIZE1 8
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	int br, bc, bcol, i, r0, r1, r2, r3, r4, r5, r6, r7;
	if (M == 64) {
		// four sets at most
		for (bc = 0; bc < M; bc += BROW) {
			for (br = 0; br < N; br += BROW) {
				// watch out for ((br * 64 + bc ) >> 3) = ((bc * 64 + br)>>3) mod 32, 
				if ((((bc - br) >> 3) & 0x1f) == 0) {
					for (bcol = 0; bcol < BROW; bcol += 4) {
						for (i = 0; i < 4; ++i) {
							r0 = A[br+i][bc+bcol];
							r1 = A[br+i][bc+bcol+1];
							r2 = A[br+i][bc+bcol+2];
							r3 = A[br+i][bc+bcol+3];
							B[bc+bcol+i][br] = r0;
							B[bc+bcol+i][br+1] = r1;
							B[bc+bcol+i][br+2] = r2;
							B[bc+bcol+i][br+3] = r3;
						}
						for (r0 = 0; r0 < 4; ++r0) {
							for (r1 = r0 + 1; r1 < 4; ++r1) {
								r2 = B[bc+bcol+r0][br+r1];
								B[bc+bcol+r0][br+r1] = B[bc+bcol+r1][br+r0];
								B[bc+bcol+r1][br+r0] = r2;
							}
						}
						for (i = 0; i < 4; ++i) {
							r0 = A[br+4+i][bc+bcol];
							r1 = A[br+4+i][bc+bcol+1];
							r2 = A[br+4+i][bc+bcol+2];
							r3 = A[br+4+i][bc+bcol+3];
							B[bc+bcol+i][br+4] = r0;
							B[bc+bcol+i][br+5] = r1;
							B[bc+bcol+i][br+6] = r2;
							B[bc+bcol+i][br+7] = r3;
						}
						for (r0 = 0; r0 < 4; ++r0) {
							for (r1 = r0 + 1; r1 < 4; ++r1) {
								r2 = B[bc+bcol+r0][br+4+r1];
								B[bc+bcol+r0][br+4+r1] = B[bc+bcol+r1][br+4+r0];
								B[bc+bcol+r1][br+4+r0] = r2;
							}
						}
					}
				} else {
					for (i = br; i < br + BROW; ++i) {
						r0 = A[i][bc];
						r1 = A[i][bc+1];
						r2 = A[i][bc+2];
						r3 = A[i][bc+3];
						r4 = A[i][bc+4];
						r5 = A[i][bc+5];
						r6 = A[i][bc+6];
						r7 = A[i][bc+7];
						B[bc][i] = r0;
						B[bc+1][i] = r1;
						B[bc+2][i] = r2;
						B[bc+3][i] = r3;
						if (br + BROW == N) {
							B[bc+9][i-br] = r4;
							B[bc+10][i-br] = r5;
							B[bc+11][i-br] = r6;
							B[bc+12][i-br] = r7;
						} else {
							B[bc][i+BROW] = r4;
							B[bc+1][i+BROW] = r5;
							B[bc+2][i+BROW] = r6;
							B[bc+3][i+BROW] = r7;
						}
					}
					for (i = bc; i < bc + BROW/2; ++i) {
						for (r0 = br; r0 < br + BROW; ++r0) {
							if (br + BROW == N)
								B[i+BROW/2][r0] = B[i+9][r0-br];
							else
								B[i+BROW/2][r0] = B[i][r0+BROW];
						}
					}
				}
			}
		}
	} else if (M == 32) {
		for (br = 0; br < N; br += BROW)
			for (bc = 0; bc < M; bc += BROW) {
				if ((((br - bc) >> 3) & 0x1f) == 0) {
					for (i = 0; i < BROW; ++i) {
						r0 = A[br+i][bc];
						r1 = A[br+i][bc+1];
						r2 = A[br+i][bc+2];
						r3 = A[br+i][bc+3];
						r4 = A[br+i][bc+4];
						r5 = A[br+i][bc+5];
						r6 = A[br+i][bc+6];
						r7 = A[br+i][bc+7];
						B[bc+i][br] = r0;
						B[bc+i][br+1] = r1;
						B[bc+i][br+2] = r2;
						B[bc+i][br+3] = r3;
						B[bc+i][br+4] = r4;
						B[bc+i][br+5] = r5;
						B[bc+i][br+6] = r6;
						B[bc+i][br+7] = r7;
					}
					for (r0 = 0; r0 < 8; ++r0) {
						for (r1 = r0+1; r1 < 8; ++r1) {
							r2 = B[bc+r0][br+r1];
							B[bc+r0][br+r1] = B[bc+r1][br+r0];
							B[bc+r1][br+r0] = r2;
						}
					}
				} else {
					for (i = br; i < br + BROW; ++i) {
						r0 = A[i][bc];
						r1 = A[i][bc+1];
						r2 = A[i][bc+2];
						r3 = A[i][bc+3];
						r4 = A[i][bc+4];
						r5 = A[i][bc+5];
						r6 = A[i][bc+6];
						r7 = A[i][bc+7];
						B[bc][i] = r0;
						B[bc+1][i] = r1;
						B[bc+2][i] = r2;
						B[bc+3][i] = r3;
						B[bc+4][i] = r4;
						B[bc+5][i] = r5;
						B[bc+6][i] = r6;
						B[bc+7][i] = r7;
					}
				}
			}
	} else {
		for (br = 0; br + 9 < N; br += 9) {
			for (bc = 0; bc + 9 < M; bc += 9) {
				for (i = br; i < br + 9; ++i) {
					r0 = A[i][bc];
					r1 = A[i][bc+1];
					r2 = A[i][bc+2];
					r3 = A[i][bc+3];
					r4 = A[i][bc+4];
					r5 = A[i][bc+5];
					r6 = A[i][bc+6];
					r7 = A[i][bc+7];
					bcol = A[i][bc+8];
					B[bc][i] = r0;
					B[bc+1][i] = r1;
					B[bc+2][i] = r2;
					B[bc+3][i] = r3;
					B[bc+4][i] = r4;
					B[bc+5][i] = r5;
					B[bc+6][i] = r6;
					B[bc+7][i] = r7;
					B[bc+8][i] = bcol;
				}
			}
		}

		for (bc = 0; bc + 9 < M; bc += 9) {
			for (i = br; i < N; ++i) {
					r0 = A[i][bc];
					r1 = A[i][bc+1];
					r2 = A[i][bc+2];
					r3 = A[i][bc+3];
					r4 = A[i][bc+4];
					r5 = A[i][bc+5];
					r6 = A[i][bc+6];
					r7 = A[i][bc+7];
					bcol = A[i][bc+8];
					B[bc][i] = r0;
					B[bc+1][i] = r1;
					B[bc+2][i] = r2;
					B[bc+3][i] = r3;
					B[bc+4][i] = r4;
					B[bc+5][i] = r5;
					B[bc+6][i] = r6;
					B[bc+7][i] = r7;
					B[bc+8][i] = bcol;
			}
		}

		for (br = 0; br < N; ++br)
			for (i = bc; i < M; ++i)
				B[i][br] = A[br][i];
	
	} 
}


char transpose_test_desc[] = "Transpose test";
void transpose_test(int M, int N, int A[N][M], int B[M][N])
{
	int br, bc, bcol, i, r0, r1, r2, r3, r4, r5, r6, r7;
	if (M == 64) {
		// four sets at most
		for (br = 0; br < N; br += BROW) {
			for (bc = 0; bc < M; bc += BROW) {
				// watch out for ((br * 64 + bc ) >> 3) = ((bc * 64 + br)>>3) mod 32, 
				if ((((bc - br) >> 3) & 0x1f) == 0) {
					for (bcol = 0; bcol < BROW; bcol += 4) {
						for (i = 0; i < 4; ++i) {
							r0 = A[br+i][bc+bcol];
							r1 = A[br+i][bc+bcol+1];
							r2 = A[br+i][bc+bcol+2];
							r3 = A[br+i][bc+bcol+3];
							B[bc+bcol+i][br] = r0;
							B[bc+bcol+i][br+1] = r1;
							B[bc+bcol+i][br+2] = r2;
							B[bc+bcol+i][br+3] = r3;
						}
						for (r0 = 0; r0 < 4; ++r0) {
							for (r1 = r0 + 1; r1 < 4; ++r1) {
								r2 = B[bc+bcol+r0][br+r1];
								B[bc+bcol+r0][br+r1] = B[bc+bcol+r1][br+r0];
								B[bc+bcol+r1][br+r0] = r2;
							}
						}
						for (i = 0; i < 4; ++i) {
							r0 = A[br+4+i][bc+bcol];
							r1 = A[br+4+i][bc+bcol+1];
							r2 = A[br+4+i][bc+bcol+2];
							r3 = A[br+4+i][bc+bcol+3];
							B[bc+bcol+i][br+4] = r0;
							B[bc+bcol+i][br+5] = r1;
							B[bc+bcol+i][br+6] = r2;
							B[bc+bcol+i][br+7] = r3;
						}
						for (r0 = 0; r0 < 4; ++r0) {
							for (r1 = r0 + 1; r1 < 4; ++r1) {
								r2 = B[bc+bcol+r0][br+4+r1];
								B[bc+bcol+r0][br+4+r1] = B[bc+bcol+r1][br+4+r0];
								B[bc+bcol+r1][br+4+r0] = r2;
							}
						}
					}
				} else {
					if (br + BROW != N) {
						for (i = br; i < br + BROW; ++i) {
							r0 = A[i][bc];
							r1 = A[i][bc+1];
							r2 = A[i][bc+2];
							r3 = A[i][bc+3];
							r4 = A[i][bc+4];
							r5 = A[i][bc+5];
							r6 = A[i][bc+6];
							r7 = A[i][bc+7];
							B[bc][i] = r0;
							B[bc+1][i] = r1;
							B[bc+2][i] = r2;
							B[bc+3][i] = r3;
							B[bc][i+BROW] = r4;
							B[bc+1][i+BROW] = r5;
							B[bc+2][i+BROW] = r6;
							B[bc+3][i+BROW] = r7;
						}
						for (i = bc; i < bc + BROW/2; ++i) {
							for (r0 = br; r0 < br + BROW; ++r0) {
									B[i+BROW/2][r0] = B[i][r0+BROW];
							}
						}
					} else {
						for (i = br; i < br + BROW; ++i) {
							r0 = A[i][bc];
							r1 = A[i][bc+1];
							r2 = A[i][bc+2];
							r3 = A[i][bc+3];
							B[bc][i] = r0;
							B[bc+1][i] = r1;
							B[bc+2][i] = r2;
							B[bc+3][i] = r3;
						}
						for (i = br; i < br + BROW; ++i) {
							r0 = A[i][bc+4];
							r1 = A[i][bc+5];
							r2 = A[i][bc+6];
							r3 = A[i][bc+7];
							B[bc+4][i] = r0;
							B[bc+5][i] = r1;
							B[bc+6][i] = r2;
							B[bc+7][i] = r3;
						}
					}
				}
			}
		}
	} else {
		bcol = 8;
		for (br = 0; br < N; br += BROW)
			for (bc = 0; bc < M; bc += bcol)
				for (i = br; i < br + BROW; ++i) {
						r0 = A[i][bc];
						r1 = A[i][bc+1];
						r2 = A[i][bc+2];
						r3 = A[i][bc+3];
						r4 = A[i][bc+4];
						r5 = A[i][bc+5];
						r6 = A[i][bc+6];
						r7 = A[i][bc+7];
						B[bc][i] = r0;
						B[bc+1][i] = r1;
						B[bc+2][i] = r2;
						B[bc+3][i] = r3;
						B[bc+4][i] = r4;
						B[bc+5][i] = r5;
						B[bc+6][i] = r6;
						B[bc+7][i] = r7;
					}
	}
}

char transpose_1_desc[] = "8 by 4";
void transpose_1(int M, int N, int A[N][M], int B[M][N])
{
	int br, bc, bcol, i, r0, r1, r2, r3, r4, r5, r6, r7;
	if (M == 64) {
		// four sets at most
		for (br = 0; br < N; br += BROW) {
			for (bc = 0; bc < M; bc += 4) {
				// watch out for ((br * 64 + bc ) >> 3) = ((bc * 64 + br)>>3) mod 32, 
				if ((((bc - br) >> 3) & 0x1f) == 0) {
					for (i = 0; i < 4; ++i) {
						r0 = A[br+i][bc];
						r1 = A[br+i][bc+1];
						r2 = A[br+i][bc+2];
						r3 = A[br+i][bc+3];
						B[bc+i][br] = r0;
						B[bc+i][br+1] = r1;
						B[bc+i][br+2] = r2;
						B[bc+i][br+3] = r3;
					}
					for (r0 = 0; r0 < 4; ++r0) {
						for (r1 = r0 + 1; r1 < 4; ++r1) {
							r2 = B[bc+r0][br+r1];
							B[bc+r0][br+r1] = B[bc+r1][br+r0];
							B[bc+r1][br+r0] = r2;
						}
					}
					for (i = 0; i < 4; ++i) {
						r0 = A[br+4+i][bc];
						r1 = A[br+4+i][bc+1];
						r2 = A[br+4+i][bc+2];
						r3 = A[br+4+i][bc+3];
						B[bc+i][br+4] = r0;
						B[bc+i][br+5] = r1;
						B[bc+i][br+6] = r2;
						B[bc+i][br+7] = r3;
					}
					for (r0 = 0; r0 < 4; ++r0) {
						for (r1 = r0 + 1; r1 < 4; ++r1) {
							r2 = B[bc+r0][br+4+r1];
							B[bc+r0][br+4+r1] = B[bc+r1][br+4+r0];
							B[bc+r1][br+4+r0] = r2;
						}
					}
				} else {
					for (i = br; i < br + BROW; ++i) {
						r0 = A[i][bc];
						r1 = A[i][bc+1];
						r2 = A[i][bc+2];
						r3 = A[i][bc+3];
						B[bc][i] = r0;
						B[bc+1][i] = r1;
						B[bc+2][i] = r2;
						B[bc+3][i] = r3;
					}
				}
			}
		}
	} else {
		bcol = 8;
		for (br = 0; br < N; br += BROW)
			for (bc = 0; bc < M; bc += bcol)
				for (i = br; i < br + BROW; ++i) {
						r0 = A[i][bc];
						r1 = A[i][bc+1];
						r2 = A[i][bc+2];
						r3 = A[i][bc+3];
						r4 = A[i][bc+4];
						r5 = A[i][bc+5];
						r6 = A[i][bc+6];
						r7 = A[i][bc+7];
						B[bc][i] = r0;
						B[bc+1][i] = r1;
						B[bc+2][i] = r2;
						B[bc+3][i] = r3;
						B[bc+4][i] = r4;
						B[bc+5][i] = r5;
						B[bc+6][i] = r6;
						B[bc+7][i] = r7;
					}
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 
    // registerTransFunction(transpose_test, transpose_test_desc);

    // registerTransFunction(transpose_1, transpose_1_desc);
    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

