#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100



int32_t main(int32_t argc, const char* argv[])
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    while (1)
    {
        printf("Введите название программы и агрументы(Max 1 5 2 8)\n");
        printf("---> ");
        if (!fgets(command, sizeof(command), stdin)) break;

        command[strcspn(command, "\n")] = 0;

        int32_t arg_count = 0;
        char *token = strtok(command, " ");
        while (token && arg_count < MAX_ARGUMENTS - 1)
        {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL; // Заканчиваем массив NULL

        if (arg_count == 0) continue;

        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Ошибка при создании родительского процесса");
        }
        else if (pid == 0)
        {
            if (execv(arguments[0], arguments) == -1)
                {
                    printf("Ошибка при запуске программы %s\n", arguments[0]);
                }
        }
        else
        {
            wait(NULL);
        }
    }
}
