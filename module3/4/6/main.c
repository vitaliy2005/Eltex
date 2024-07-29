#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>

#define FILENAME "numbers.txt"

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

    sem_t *semaphore = sem_open("/my_semaphore", 0);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    int32_t semValue;
    for (int i = 0; i < count; i++)
    {
        sleep(4);
        sem_wait(semaphore);
        sem_getvalue(semaphore, &semValue);
        printf("----%d\n", semValue);
        printf("Родитель: Чтение чисел из файла...\n");
        read_numbers_from_file();
        sleep(1);
        sem_post(semaphore);
    }
    sem_close(semaphore);
    sem_unlink("/my_semaphore");

    return EXIT_SUCCESS;
}
