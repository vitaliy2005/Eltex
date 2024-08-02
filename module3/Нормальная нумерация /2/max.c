#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>




int main(int32_t argc, char* argv[])
{
    int32_t max = -100000000;
    for(int32_t i = 1; i < argc; i++)
    {
        if (atoi(argv[i]) > max)
        {
            max = atoi(argv[i]);
        }
    }
    printf("максимальное число - %d\n", max);
}
