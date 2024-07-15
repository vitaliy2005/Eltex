#include <stdint.h>
#include <stdio.h>


typedef struct
{
    char symbolOperation[4];
    double (*FucnOperation)(double, double);
}Operation;

double max(double a, double b);
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
