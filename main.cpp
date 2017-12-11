#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define SEED 35791246

main(int argc, char* argv)
{
    int iterations=1000000;
    float x,y;
    int i,count=0; /* # of points in the 1st quadrant of unit circle */
    float z;
    float pi;



    /* initialize random numbers */
    srand(SEED);
    count=0;
    int np = omp_get_num_procs();
    omp_set_num_threads(np);
#pragma omp parallel for private(x,y,z)
    for ( i=0; i<iterations; i++) {
        x = (float)rand()/RAND_MAX;
        y = (float)rand()/RAND_MAX;
        z = x*x+y*y;
        if (z<=1) {
#pragma omp critical
            count++;
        }
    }
    pi=(float)count/iterations*4;
    printf(" estimate of pi is %f \n",pi);
}