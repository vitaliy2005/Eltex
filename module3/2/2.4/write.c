#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

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

    srand(time(NULL));

    while (1)
    {
        int randomNumber = rand() % 100 + 1;
        write(fd, &randomNumber, sizeof(randomNumber));
        printf("Записано: %d\n", randomNumber);
        sleep(1);
    }

    close(fd);

    return 0;
}
