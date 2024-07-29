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
#include <sys/sem.h>
#include <errno.h>

#define FILENAME "numbers.txt"


void operate_semaphore(int semid, int semnum, int op) {
    struct sembuf sb;

    sb.sem_num = semnum; // Номер семафора в множестве
    sb.sem_op = op;      // Операция (+ для увеличения, - для уменьшения)
    sb.sem_flg = 0;      // Флаги (0 – блокирующая операция)

    if (semop(semid, &sb, 1) == -1) {
        perror("semop failed");
        exit(EXIT_FAILURE);
    }
}

void generate_random_numbers(int32_t semid, int32_t count)
{
    srand(time(NULL));
    int32_t openFlags = O_CREAT|O_RDWR|O_APPEND;
    int32_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    char buf[256];
    while (1)
    {
        if ((semctl(semid, 0, GETVAL) == 1) &&( count != 0))
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

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("Ошибка при создании канала");
        return EXIT_FAILURE;
    }

    int semid = semget(1234, 1, IPC_CREAT | 0666);
    if (semid == -1)
    {
        fprintf(stderr, "semget IPC_RMID failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (semctl(semid, 0, SETVAL, 1) == -1)
    {
        fprintf(stderr, "semget setval failed: %s\n", strerror(errno));
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Ошибка при вызове fork");
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        close(pipe_fd[0]);
        generate_random_numbers(semid, count);
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(pipe_fd[1]);
        for (int i = 0; i < count; i++)
        {
            sleep(2);
            operate_semaphore(semid, 0, -1);

            printf("Родитель: Чтение чисел из файла...\n");
            read_numbers_from_file();

            operate_semaphore(semid, 0, 1);
        }
        wait(NULL);

        if (semctl(semid, 0, IPC_RMID) == -1)
        {
            perror("semctl IPC_RMID failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[0]);
    }

    return EXIT_SUCCESS;
}
