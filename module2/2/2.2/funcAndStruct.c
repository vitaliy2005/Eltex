#include "funcAndStruct.h"


double max(double a, double b)
{
    return 2;
}


double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
    {
        printf("Ошибка: деление на ноль\n");
        return 0;
    }
    return a / b;
}
