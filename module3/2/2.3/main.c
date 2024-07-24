#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 100
#define MAX_COMMANDS 10

void execute_command(char *cmd) {
    char *commands[MAX_COMMANDS];
    int32_t num_commands = 0;

    commands[num_commands++] = strtok(cmd, "|");
    while ((commands[num_commands] = strtok(NULL, "|")) != NULL)
    {
        num_commands++;
    }
    int32_t pipe_fd[num_commands-1][2];

    for (int i = 0; i < num_commands - 1; i++)
    {
        if (pipe(pipe_fd[i]) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    pid_t pids[num_commands];

    for (int32_t i = 0; i < num_commands; i++)
    {
        pids[i] = fork();

        if (pids[i] < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pids[i] == 0)
        {
            if (i > 0)
            { // Если это не первая команда
                dup2(pipe_fd[i-1][0], STDIN_FILENO); // Вход из предыдущего канала
            }
            if (i < num_commands - 1)
            { // Если это не последняя команда
                dup2(pipe_fd[i][1], STDOUT_FILENO); // Выход в следующий канал
            }

            for (int32_t j = 0; j < num_commands; j++)
            {
                for (int32_t k = 0; k < 2; k++)
                {
                    close(pipe_fd[j][k]);
                }
            }

            char *args[MAX_ARGS];
            char *token = strtok(commands[i], " ");
            int arg_count = 0;

            while (token != NULL)
            {
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL;

            execv(args[0], args);
        }
    }

    for (int32_t j = 0; j < num_commands; j++)
    {
        for (int32_t k = 0; k < 2; k++)
        {
            close(pipe_fd[j][k]);
        }
    }

    int32_t status, ret;
    for (int i = 0; i < num_commands; i++)
    {

        waitpid(pids[i], &status, 0);
        ret = WEXITSTATUS(status);
        printf("%d - ret\n", ret);
    }
}

int main()
{
    char line[MAX_LINE];

    while (1) {
        printf("shell> ");
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL)
        {
            perror("fgets");
            continue;
        }

        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) break;

        execute_command(line);
    }

    return 0;
}
