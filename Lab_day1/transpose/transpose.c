/*
 * This code is created for teaching purpose at the ICTP SMR3187 activity 
 * "Latin American Introductory School on Parallel Programming and Parallel Architecture for High Performance Computing"
 *
 * Author: Ivan Girotto (igirotto@ictp.it)
 * Last Revision: Feb 2018
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>


double cclock()
  /* Returns elepsed seconds past from the last call to timer rest */
{

    struct timeval tmp;
    double sec;
    gettimeofday( &tmp, (struct timezone *)0 );
    sec = tmp.tv_sec + ((double)tmp.tv_usec)/1000000.0;
    return sec;
}

int main( int argc, char * argv [] ) {

  double * A, * AT;
  int i, j;
  double t_start, t_end;
  int BLOCKSIZE, MATRIXDIM;

  if( argc < 2 ){
    fprintf( stderr, "Error. The program runs as following: %s [MATRIXDIM].\nProgram exit ...\n", argv[0]);
    exit(1);
  }

  MATRIXDIM=atoi(argv[1]);

  if( MATRIXDIM < 1 ){
    fprintf( stderr, "Error. Inconsistent parameters.\nProgram exit ...\n" );
    exit(1);
  }

  A = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );
  AT = ( double * ) malloc( MATRIXDIM * MATRIXDIM * sizeof( double ) );

  for( i = 0; i < MATRIXDIM * MATRIXDIM; i++ ){
    A[i] = (double) i;
  }
  
  t_start=cclock();
  for( i = 0; i < MATRIXDIM; i++ ){
    for( j = 0; j < MATRIXDIM; j++ ){
      AT[ ( j * MATRIXDIM ) + i ] = A[ ( i * MATRIXDIM ) + j ];
    }
  }
  t_end=cclock(); 

  free( A );
  free( AT );
  fprintf( stdout, " Matrix transpose executed. Time Elapsed %9.4f secs\n", t_end-t_start );

  return 0;
}
