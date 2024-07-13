#include <stdio.h>
#include <stdint.h>


int main()
{
    double a, b;
    char typeOperation[1];
    while (1)
    {
        printf("Введите первое число\n");
        scanf("%lf", &a);

        printf("Введите тип операции('+', '-', '*', '/'), 0 - для выхода\n");
        scanf("%s", typeOperation);

        if (*typeOperation == '0') break;

        printf("Введите второе число\n");
        scanf("%lf", &b);

        if (*typeOperation == '+')
            printf("Результат %f\n", a + b);
        else if (*typeOperation == '-')
            printf("Результат %f\n", a - b);
        else if (*typeOperation == '*')
            printf("Результат %f\n", a * b);
        else if (*typeOperation == '/')
        {
            if (b != 0)
                printf("Результат %f\n", a / b);
            else
            {
                printf("На ноль делить нельзя\n");
            }
        }
        else
            printf("Данной операции не существует\n");
    }

}
