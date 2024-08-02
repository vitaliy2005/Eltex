#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>





int main(int32_t argc, char* argv[])
{
    pid_t childPid = fork();

    if (childPid == -1)
    {
        perror("Ошибка при создании дочернего процесса");
    }
    else if(childPid == 0)
    {
        printf("Площадь квадратов посчитанная в дочернем процессе\n");
        for (int32_t i = (argc/2) + 1; i < argc; i++)
            printf("Площадь квадрата со стороной %d = %d\n", atoi(argv[i]), atoi(argv[i])*atoi(argv[i]));
    }
    else
    {
        printf("Площадь квадратов посчитанная в родителе\n");
        for (int32_t i = 1; i < (argc/2) + 1; i++)
            printf("Площадь квадрата со стороной %d = %d\n", atoi(argv[i]), atoi(argv[i])*atoi(argv[i]));
    }
}
