#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define FILENAME "numbers.txt"

volatile sig_atomic_t file_access = 1;
volatile sig_atomic_t number = 0;


void signal_handler(int signo)
{
    if (signo == SIGUSR1)
    {
        file_access = 0;
    }
    else if (signo == SIGUSR2)
    {
        file_access = 1;
    }
}

void generate_random_numbers(int32_t write_fd)
{
    srand(time(NULL));
    while (1)
    {
        if (file_access)
        {
            int randomNumber = rand() % 100;
            int32_t outputFd, openFlags;
            mode_t filePerms ;
            int32_t numRead;
            char buf[256];
            strcpy(buf, "");

            openFlags = O_CREAT|O_RDWR|O_APPEND;
            filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

            outputFd = open(FILENAME, openFlags, filePerms);
            if (outputFd == -1)
            {
                printf ("Ошибка открытия файла %s\n ", "contact.txt");
                return;
            }
            int len = snprintf(buf, sizeof(buf), "%d\n", randomNumber);
            write(outputFd, buf, len);
            close(outputFd);

            sleep(2);
        }
        else
        {
            sleep(1);
        }
    }
}

void read_numbers_from_file()
{
    int32_t inputFd, numRead;
    char buf[1024];
    strcpy(buf, "");

    inputFd = open(FILENAME, O_RDONLY);
    if (inputFd == -1)
    {
        printf ("Error opening file contact.txt\n");
        return;
    }
    while((numRead = read(inputFd, buf, sizeof(buf))) > 0)
    {
        buf[numRead] = '\0';
        printf("%s", buf);
    }

    close(inputFd);
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Использование: %s <количество чисел>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int count = atoi(argv[1]);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Ошибка при создании канала");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Ошибка при вызове fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        close(pipe_fd[0]);
        generate_random_numbers(pipe_fd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[1]);

        for (int i = 0; i < count; i++)
        {
            sleep(2);

            kill(pid, SIGUSR1);

            printf("Родитель: Чтение чисел из файла...\n");
            read_numbers_from_file();

            kill(pid, SIGUSR2);
        }

        close(pipe_fd[0]);
    }

    return EXIT_SUCCESS;
}
