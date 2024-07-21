#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void end()
{
    printf("Успешное завершение работы прорамммы\n");
}

int main(int32_t argc, const char* argv[])
{
    pid_t childPid = fork();

    if (childPid == -1)
    {
        perror("Ошибка при создании дочернего процесса");
    }
    else if(childPid == 0)
    {
        printf("Вывод аргументов командной строки в дочернем процессе\n");
        for (int32_t i = 0; i < argc; i++)
        {
            printf("аргумент n%d %s\n", i+1, argv[i]);
        }
        end();
    }
    else
    {
        printf("Вывод аргументов командной строки в родителе\n");
        for (int32_t i = 0; i < argc; i++)
        {
            printf("аргумент n%d %s\n", i+1, argv[i]);
        }
        end();
    }
}
