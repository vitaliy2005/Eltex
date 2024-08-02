#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t sigint_count = 0;

void handle_sigint(int32_t sig)
{
    sigint_count++;
    if (sigint_count >= 3)
    {
        printf("Received SIGINT 3 times. Exiting...\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        printf("Received SIGINT %d times.\n", sigint_count);
    }
}

int main()
{
    signal(SIGINT, handle_sigint);
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
