#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>



typedef struct
{
    char symbolOperation[4];
    double (*FucnOperation)(double, double);
}Operation;


double (*addD)(double, double);
double (*subtractD)(double, double);
double (*multiplyD)(double, double);
double (*divideD)(double, double);
