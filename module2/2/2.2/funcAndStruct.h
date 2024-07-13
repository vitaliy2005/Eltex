#include <stdint.h>
#include <stdio.h>


typedef struct
{
    char symbolOperation;
    double (*FucnOperation)(double, double);
}Operation;

double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
