#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <errno.h>

#define FILENAME "numbers.txt"
int semid;

void signal_handler(int signo)
{
    if (semctl(semid, 0, IPC_RMID) == -1)
    {
        perror("semctl IPC_RMID failed");
        exit(EXIT_FAILURE);
    }
}

void operate_semaphore(int semid, int semnum, int op)
{
    struct sembuf sb;

    sb.sem_num = semnum;
    sb.sem_op = op;
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1)
    {
        perror("semop failed");
        exit(EXIT_FAILURE);
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

    semid = semget(1234, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        fprintf(stderr, "semget IPC_RMID failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (semctl(semid, 0, SETVAL, 2) == -1)
    {
        fprintf(stderr, "semget setval failed: %s\n", strerror(errno));
    }
    signal(SIGINT, signal_handler);


    for (int i = 0; i < count; i++)
    {
        sleep(4);
        if (semctl(semid, 0, GETVAL) > 0)
        {
            operate_semaphore(semid, 0, -1);
            printf("Родитель: Чтение чисел из файла...\n");
            read_numbers_from_file();
            sleep(3);
            operate_semaphore(semid, 0, 1);
        }
        else
        {
            printf("Количесвто процессов для чтения ограничено\n");
        }
    }

    return EXIT_SUCCESS;
}
