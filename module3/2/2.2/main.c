#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define AMOUNT_NUMBER 25

int main()
{
    int pipe1[2];
    int pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        int32_t number;

        srand(time(NULL));

        close(pipe1[1]);
        close(pipe2[0]);
        int32_t i = 0;
        while (i++ < AMOUNT_NUMBER)
        {
            number = rand() % 256;
            write(pipe2[1], &number, sizeof(int));
            read(pipe1[0], &number, sizeof(int));
            printf("получено умноженное число от родителя - %d\n", number);
        }

        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe1[0]);
        close(pipe2[1]);

        int32_t number;
        int32_t i = 0;
        while (i++ < AMOUNT_NUMBER)
        {
            read(pipe2[0], &number, sizeof(int));
            printf("Получено число от потомка - %d\n", number);
            number *= 2;
            write(pipe1[1], &number, sizeof(int));
        }


        close(pipe1[1]); // Закрываем запись в первом канале
        close(pipe2[0]); // Закрываем чтение во втором канале

        wait(NULL); // Ожидаем завершения дочернего процесса
    }

    return 0;
}
