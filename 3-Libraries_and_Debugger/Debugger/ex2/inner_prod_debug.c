#include <stdio.h>
/* This code contains some logical errors. Try using GDB to find out */
/* For two given 2 by 1 vectors 1 and 2, compute the inner product */
double inner(double *a, double *b, int n);

void main()
{
    int i, j;
    double a[2][2], r;
    for(i=0; i<2; i++) {
        printf("Vector %d:\n", (i+1));
        printf("1st element:");
        scanf("%f", &a[i][1]);
        printf("2nd element:");
        scanf("%f", &a[i][2]);
    }
    r = inner(a[0], a[1], 2);
    printf("The inner product is %f\n", r);
}

double inner(double *a, double *b, int n) 
{
    int i, res;
    for(i=0; i<n; i++) 
    {
        res = res + a[i]*b[i];
    }
    return res;
}
