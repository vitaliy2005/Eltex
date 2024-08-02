#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/sem.h>

#define FIFO_NAME "fifo"

int main()
{
    mkfifo(FIFO_NAME, 0666);

    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int32_t semid;
    struct sembuf semBufAdd = {0, 1, 0};
    struct sembuf semBufSub = {0, -1, 0};

    key_t key;
    if((key = ftok("sem", 0)) < 0)
    {
        perror("key-gen error");
    }
    if ((semid = semget(key, 1, 0666 | IPC_CREAT) < 0))
    {
        perror("sem error");
    }

    srand(time(NULL));

    while (1)
    {
        if (semop(semid, &semBufSub, 1))
        {
            perror("semop error");
        }
        int randomNumber = rand() % 100 + 1;
        write(fd, &randomNumber, sizeof(randomNumber));
        printf("Записано: %d\n", randomNumber);
        sleep(1);
    }

    close(fd);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
