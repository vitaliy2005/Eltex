#include "funcAndStruct.h"




int main()
{
    int32_t firstDight, secondDight;
    char typeOperation[5];

    Operation operations[] = {
            {"+", add},
            {"-", subtract},
            {"*", multiply},
            {"/", divide},
            {"max", max}};
    while (1)
    {
        printf("Введите первое число\n");
        scanf("%d", &firstDight);

        printf("Введите тип операции('+', '-', '*', '/'), 0 - для выхода\n");
        scanf("%s", typeOperation);

        if (*typeOperation == '0') break;

        printf("Введите второе число\n");
        scanf("%d", &secondDight);

        for (int32_t i = (sizeof(operations)/sizeof(Operation))-1; i >= 0; i--)
        {

            if (operations[i].symbolOperation == *typeOperation)
            {
                printf("Резултат равен %f\n", operations[i].FucnOperation(firstDight, secondDight));
                break;
            }
            else if (i == 0)
            {
                printf("Данной команды не существует\n");
            }
        }
    }
}
