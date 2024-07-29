#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

#define FILENAME "./numbers.txt"

void generate_random_numbers(int32_t count, sem_t* semaphore)
{
    srand(time(NULL));
    int32_t openFlags = O_CREAT|O_RDWR|O_APPEND;
    int32_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    char buf[256];
    int32_t semValue;
    while (1)
    {
        sem_getvalue(semaphore, &semValue);
        if ((semValue == 1) && ( count != 0))
        {
            int32_t randomNumber = rand() % 100;
            int32_t outputFd;
            int32_t numRead;
            strcpy(buf, "");

            outputFd = open(FILENAME, openFlags, filePerms);
            if (outputFd == -1)
            {
                perror ("Ошибка открытия файла %s\n ");
                return;
            }
            int len = snprintf(buf, sizeof(buf), "%d\n", randomNumber);
            write(outputFd, buf, len);

            close(outputFd);
            sleep(1);
            count--;
        }
        else
        {

            if(count == 0)
                break;
            printf("%d\n", semValue);
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
        perror ("Ошибка чтения");
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

    sem_t *semaphore = sem_open("/semm", O_CREAT, 0666, 1);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    sem_init(semaphore, 0, 1);
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Ошибка при вызове fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        generate_random_numbers(count, semaphore);
        exit(EXIT_SUCCESS);
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            sleep(2);
            sem_wait(semaphore);
            printf("Родитель: Чтение чисел из файла...\n");
            read_numbers_from_file();
            sem_post(semaphore);
        }

        wait(NULL);
        sem_destroy(semaphore);
    }

    return EXIT_SUCCESS;
}
