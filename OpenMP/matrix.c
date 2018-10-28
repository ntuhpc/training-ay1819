#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 600
#define M 600
#define K 600

int main () {

    /* Arrays for doing the calculation in parallel. */
    double A[M][K], B[K][N], C[M][N];
    
    /* Array for doing the calculation in serial. */
    double CS[M][N];

    const double ALPHA = 2.1, BETA = 3.2;

    /* Variables find the biggest difference between the parallel and serial versions */
    double diff, max_diff;

    /*
      Timing variables
    */
    double serial_start, serial_finish;
    double parallel_start, parallel_finish;

    int i, j, l;

    /* Initialize the matrices */

    for (j=0;j<M;j++) {
	for(l=0;l<K;l++) {
	    A[j][l] = j * l;
	}
    }

    for(l=0;l<K;l++) {
      for (j=0;j<N;j++) {
	    B[l][j] = j * l;
	}
    }

    for(i=0;i<M;i++) {
	for(j=0;j<N;j++) {
	    C [i][j] = 0.0;
	    CS[i][j] = 0.0;
	}
    }


    parallel_start = omp_get_wtime();

    /* 
       PARALLELIZE THIS LOOP NEST
    */
    for(i=0;i<M;i++) {
	
	for(j=0;j<N;j++) {
	    C[i][j] = BETA * C[i][j];
	    for(l=0;l<K;l++) {
		C[i][j] = C[i][j] + ALPHA * A[i][l] * B[l][j];
	    }
	}
	
    }

    parallel_finish = omp_get_wtime();

    /*
      Serial version for comparison.
    */

    serial_start = omp_get_wtime();

    for(i=0;i<M;i++) {
      for(j=0;j<N;j++) {
	    CS[i][j] = BETA * CS[i][j];
	    for(l=0;l<K;l++) {
		CS[i][j] = CS[i][j] + ALPHA * A[i][l] * B[l][j];
	    }
	}	
    }

    serial_finish = omp_get_wtime();

    /*
      Checking of output for correctness.
    */
    
    max_diff = 0.0;
    for(j=0;j<N;j++) {
	for(i=0;i<M;i++) {
	  diff=fabs(C[i][j]- CS[i][j]); 
	  if(diff>max_diff) {
	    max_diff=diff;
	  }
	}
    }

    printf("Parallel version took %f seconds\n",parallel_finish - parallel_start);
    printf("Serial version took %f seconds\n",serial_finish - serial_start);
    printf("Maximum difference between versions=%22.16f\n",max_diff);

    return 0;

}
