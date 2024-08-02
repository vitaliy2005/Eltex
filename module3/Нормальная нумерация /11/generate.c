#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

#define FILENAME "numbers.txt"

int main()
{
    srand(time(NULL));
    int32_t count = 25;
    int32_t openFlags = O_CREAT|O_RDWR|O_APPEND;
    int32_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    char buf[256];
    int32_t semValue;
    sem_t *semaphore = sem_open("/my_semaphore", O_CREAT, 0644, 2);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        sem_getvalue(semaphore, &semValue);
        printf("%d\n", semValue);
        if ((semValue>= 2) && (count != 0))
        {
            int32_t randomNumber = rand() % 100;
            int32_t outputFd;
            int32_t numRead;
            strcpy(buf, "");

            outputFd = open(FILENAME, openFlags, filePerms);
            if (outputFd == -1)
            {
                perror ("Ошибка открытия файла %s\n ");
                return -1;
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
            printf("Файл читается, запись не возможна\n");
            sleep(1);
        }
    }
    sem_close(semaphore);
    sem_unlink("/my_semaphore");
}
