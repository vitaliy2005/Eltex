#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("Received SIGINT signal (Ctrl + C).\n");
    }
    else if (sig == SIGQUIT)
    {
        printf("Received SIGQUIT signal (Ctrl + \\).\n");
    }
}

int main()
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
    FILE *file = fopen("counter_output.txt", "a");
    if (file == NULL)
    {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    int32_t counter = 1;
    while (1)
    {
        fprintf(file, "%d\n", counter++);
        fflush(file);
        sleep(1);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
