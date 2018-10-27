#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "MatUtil.h"
#include "Floyd_openMP.h"

int main(int argc, char **argv)
{
    struct timeval tv1, tv2;

    if(argc != 2)
    {
        printf("Usage: test {N}\n");
        exit(-1);
    }

    //generate a random matrix.
    size_t N = atoi(argv[1]);
    int *mat = (int*)malloc(sizeof(int)*N*N);
    GenMatrix(mat, N);

    //compute the reference result.
    int *ref = (int*)malloc(sizeof(int)*N*N);
    memcpy(ref, mat, sizeof(int)*N*N);
    gettimeofday(&tv1, NULL);
    Floyd_Warshall_ST(ref, N);
    gettimeofday(&tv2, NULL);
    long sequentialtime = (tv2.tv_sec - tv1.tv_sec)*1000000 + tv2.tv_usec - tv1.tv_usec;
    printf("Elapsed time (sequential) = %ld usecs\n", sequentialtime);

    //compute your results
    int *result = (int*)malloc(sizeof(int)*N*N);
    memcpy(result, mat, sizeof(int)*N*N);

    //replace by parallel algorithm
    gettimeofday(&tv1, NULL);
    Floyd_Warshall_OpenMP(result, N);
    gettimeofday(&tv2, NULL);
    long paralleltime = (tv2.tv_sec - tv1.tv_sec)*1000000 + tv2.tv_usec - tv1.tv_usec;
    printf("Elapsed time (parallel) = %ld usecs\n", paralleltime);
    printf("Speed up = %.3lf\n", (double)sequentialtime/paralleltime);
    
    //compare your result with reference result
    if(CmpArray(result, ref, N*N))
        printf("Your result is correct.\n");
    else
        printf("Your result is wrong.\n");
}
