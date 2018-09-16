#include <stdio.h>
/* This code contains some logical errors. Try using GDB to find out */
/* For two given 2 by 1 vectors 1 and 2, compute the inner product */
double inner(double *a, double *b, int n);

main()
{
    int i=0, j=0;
    double a[2][2], r=0.0;
    for(i=0; i<2; i++) {
        printf("Vector %d:\n", (i+1));
        printf("1st element:");
	//a[i][2] was out of index
	scanf("%lf", &a[i][0]);
        printf("2nd element:");
        scanf("%lf", &a[i][1]);
    }
    r = inner(a[0], a[1], 2);
    printf("The inner product is %lf\n", r);
}

double inner(double * a, double * b, int n) 
{
    // res was not initialized
    int i, res=0;
    for(i=0; i<n; i++) 
    {
        res = res + a[i]*b[i];
    }
    return res;
}
