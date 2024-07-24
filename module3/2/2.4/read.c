#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

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

    while (1)
    {
        if (read(fd, &random_number, sizeof(random_number)) > 0)
            printf("Прочитано: %d\n", random_number);
    }

    close(fd);

    return 0;
}
