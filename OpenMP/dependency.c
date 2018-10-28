#include <stdio.h>

int main () {

    int N = 12000; 
    /*
      Declare a series of arrays.
      AS is for serial version, AP for the parallel method.
    */
    double AS[N][N], AP[N][N];
    double X = 3;
    /*
      Variable set if error found with parallel version
    */
    int error = 0;

    int i, j, k;

    /*
      ARRAY INITIALISATION
    */

    for(j=0;j<N;j++) {
	for (i=0;i<N;i++) {
	    AP[i][j] = i * j;
	    AS[i][j] = i * j;
	}
    }

    /*
      PARALLELISE THIS SECTION
      Serial version to be parallelised
    */
    for(k=0;k<5;k++) {
	for(i=1;i<N;i++) {
	    for(j=0;j<N;j++) {
		AP[i][j] = AP[i-1][j] + X + (double)k;
	    }
	}
    }
    /*
      SERIAL COMPUTATION
      Serial version for testing correctness
    */
    for(k=0;k<5;k++) {
	for(i=1;i<N;i++) {
	    for(j=0;j<N;j++) {
		AS[i][j] = AS[i-1][j] + X + (double)k;
	    }
	}
    }


    /*
      TEST FOR SUCCESS 
      Compare results of each parallel version with the serial results.
    */
    
    for(j=0;j<N;j++) {
	for(i=1;i<N;i++) {
	    if(AP[i][j] != AS[i][j]) {
		error = 1;
	    }
	}
    }

    if (error == 0)
	printf("No error encountered with the parallelisation.\n");
    else
	printf("Error encountered with the parallelisation.\n");
    

    return 0;

}
