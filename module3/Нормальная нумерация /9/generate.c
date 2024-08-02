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
#include <sys/sem.h>
#include <errno.h>

#define FILENAME "numbers.txt"

int main()
{
    int semid = semget(1234, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        fprintf(stderr, "semget IPC_RMID failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, SETVAL, 2) == -1)
    {
        fprintf(stderr, "semget setval failed: %s\n", strerror(errno));
    }
    srand(time(NULL));
    int32_t count = 40;
    int32_t openFlags = O_CREAT|O_RDWR|O_APPEND;
    int32_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    char buf[256];
    while (1)
    {
        if ((semctl(semid, 0, GETVAL) >= 2) && (count != 0))
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

}
