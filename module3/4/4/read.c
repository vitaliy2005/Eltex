#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>



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
    sem_t *semaphore = sem_open("/sem", 0);
    if (semaphore == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    int32_t count = 10;
    while (count-- != 0)
    {
        sem_wait(semaphore);
        if (read(fd, &random_number, sizeof(random_number)) > 0)
            printf("Прочитано: %d\n", random_number);
    }

    close(fd);
    sem_destroy(semaphore);

    return 0;
}
