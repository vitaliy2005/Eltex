#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/sem.h>


#define FIFO_NAME "fifo"

int main() {
    int fd;
    int random_number;

    fd = open(FIFO_NAME, O_RDONLY);
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

    while (1)
    {
        if (read(fd, &random_number, sizeof(random_number)) > 0)
            printf("Прочитано: %d\n", random_number);
        if (semop(semid, &semBufAdd, 1))
        {
            perror("semop error");
        }
    }

    close(fd);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
