#ifndef MATUTIL_H
#define MATUTIL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// Generate a random matrix.
//
// Parameters:
// int *mat - pointer to the generated matrix. mat should have been 
//            allocated before callling this function.
// const int N - number of vertices.
void GenMatrix(int *mat, const size_t N);

/// Compare the content of two integer arrays. Return true if they are
// exactly the same; otherwise return false.
//
// Parameters:
// const int *l, const int *r - the two integer arrays to be compared.
// const int eleNum - the length of the two matrices.
bool CmpArray(const int *l, const int *r, const size_t eleNum);

/// Compute All-Pair's Shortest Path (APSP) using single thread. 
//
// Parameters:
// int *mat - the input matrix storing the distance values between vertices. 
//            mat should have been allocated before callling this function.
//            The result will be directed stored in mat.
// const int N - the number of vertices.
void Floyd_Warshall_ST(int *mat, const size_t N);

#endif
