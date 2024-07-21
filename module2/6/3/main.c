#include "funcAndStruct.h"



int main()
{
    int32_t firstDight, secondDight;
    char typeOperation[5];
    void* handleAdd = dlopen ("./libadd.so", RTLD_LAZY);
    void* handleSubtract = dlopen ("./libsubtract.so", RTLD_LAZY);
    void* handleMultiply = dlopen ("./libmultiply.so", RTLD_LAZY);
    void* handledivide = dlopen ("./libdivide.so", RTLD_LAZY);
    if (!handleAdd && !handleSubtract && !handleMultiply && !handledivide)
    {
        fputs (dlerror(), stderr);
        exit(1);
    }
    addD = dlsym(handleAdd, "add");
    subtractD = dlsym(handleSubtract, "subtract");
    multiplyD = dlsym(handleMultiply, "multiply");
    divideD = dlsym(handledivide, "divide");
    Operation operations[] = {
            {"+", addD},
            {"-", subtractD},
            {"*", multiplyD},
            {"/", divideD}};
    while (1)
    {
        printf("Введите первое число\n");
        scanf("%d", &firstDight);

        printf("Введите тип операции(");
        int32_t i = 0;
        while (i < (sizeof(operations)/sizeof(Operation)))
        {
            printf("'%s' ", operations[i++].symbolOperation);
        }
        printf("), 0 - для выхода\n");
        scanf("%s", typeOperation);

        if (*typeOperation == '0') break;

        printf("Введите второе число\n");
        scanf("%d", &secondDight);

        for (int32_t i = (sizeof(operations)/sizeof(Operation))-1; i >= 0; i--)
        {

            if (operations[i].symbolOperation[0] == typeOperation[0])
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
