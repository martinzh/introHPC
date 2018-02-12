/*
 * This code is created for teaching purpose at the ICTP SMR3187 activity
 * "Latin American Introductory School on Parallel Programming and Parallel Architecture for High Performance Computing"
 *
 * Author: Ivan Girotto (igirotto@ictp.it)
 * Last Revision: Feb 2018
 *
 *
 *
 *                              *** EXERCISE ***
 *
 * a) Implement the missing part of this code which aims to execute C = A x B
 *    where A,B,C are matrixes in double precision of size = SIZE x SIZE
 *
 * b) compile the code using different levels of compiler optimization (0, 1, 2, 3),
 *    run the executable and analize the performance results.
 *
 *    1) icc -o exec_matmul.x matmul_solution.c -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread
 *    2) icc -o -O0 exec_matmul.x matmul_solution.c -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread
 *    3) icc -o -O1 exec_matmul.x matmul_solution.c -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread
 *    4) icc -o -O2 exec_matmul.x matmul_solution.c -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread
 *    5) icc -o -O3 exec_matmul.x matmul_solution.c -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread
 *
 * c) compile the code adding the option for compiler vectorization, -mCORE-AVX2,
 *    suitable for the computer architectures of the Abacus system: Intel Haswell E5-2697V3
 *
 * d) answer to the following questions:
 *    What is the default level of optimization used by the Intel compiler?!
 *
 * e) would you be able to compute the number of FLOP/s performed by the matmul?!
 *
 * NOTE: make all execution using a SLURM script example provided
 *
 * http://wiki.edomex.cinvestav.mx/index.php/Guia_de_Usuario
 *
 * SUGGESTION: it is interesting to repeat the same exercise using GNU compiler and generic a BLACS library
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <mkl_cblas.h>

/* Define the Matrix size */
#define SIZE 2048


/* Return the second elapsed since Epoch (00:00:00 UTC, January 1, 1970) */
double seconds()
{
  struct timeval tmp;
  double sec;
  gettimeofday( &tmp, (struct timezone *)0 );
  sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
  return sec;
}


int main(int argc, char * argv[]){

  /* Variables Declaration */
  double *A, *B, *C, *C_BLAS;
  int i = 0, j = 0, k = 0;
  double t_start, t_end, res;

  /* Dynamic Memory Allocation */
  // A = (double*) malloc(SIZE * SIZE * sizeof(double));
  // B = (double*) malloc(SIZE * SIZE * sizeof(double));
  // C = (double*) malloc(SIZE * SIZE * sizeof(double));

  A = (double*) calloc(SIZE*SIZE, sizeof(double));
  B = (double*) calloc(SIZE*SIZE, sizeof(double));
  C = (double*) calloc(SIZE*SIZE, sizeof(double));

  /* Initialization to 0.0 for the output matrixes */
  memset( C, 0, SIZE * SIZE * sizeof(double) );
  memset( C_BLAS, 0, SIZE * SIZE * sizeof(double) );

  /* Initialization (random values) for the input matrixes */
  for( i = 0; i < SIZE; i++ ){
    for( j = 0; j < SIZE; j++ ){
        A[i][j] = rand();
        B[i][j] = rand();
    }
  }

  /* Start the timer */
  t_start = seconds();

  /* Naive implementation of a matrix multiplication */
    for( i = 0; i < SIZE; i++ ){
        for( j = 0; j < SIZE; j++ ){
            res = 0.0;
            for( k = 0; k < SIZE; k++ ){
                res += A[i][k] * B[k][j];
            }
            C[i][j] = res;
        }
    }

  /* Stop the timer */
  t_end = seconds();

  /* Print on standard output the obtained time to solution using "naive" implementation */
  fprintf( stdout, "\n\tMatrix Multiplication completed. Time to solution of \"naive\" version = %.3g seconds\n\n", t_end - t_start );

  /* execution of a Matrix Multiplication C = A x B, using Linux internal BLAS library */
  t_start = seconds();

  /* Execution of DGEMM operation using standard BLAS interface */
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, 1.0, A, SIZE, B, SIZE, 0.0, C_BLAS, SIZE);

  t_end = seconds();

  /* Print on standard output the obtained time to solution using "DGEMM" standard BLAS interface */
  fprintf( stdout, "\n\tMatrix Multiplication completed. Time to solution of Linux internal BLAS version = %.3g seconds\n\n", t_end - t_start );

  /* Memory deallocation */
  free(A);
  free(B);
  free(C);

  return 0;
}
