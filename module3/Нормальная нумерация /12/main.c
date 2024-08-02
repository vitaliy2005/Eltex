#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <wait.h>

#define SHM_SIZE 1024
#define MAX_NUMBERS 100

int shmid;
int *shm_ptr;

void handle_sigint(int sig)
{
    printf("\nЗавершение работы. Обработано наборов данных: %d\n", shm_ptr[0]);
    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}

int main()
{
    signal(SIGINT, handle_sigint);

    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (int *) -1)
    {
        perror("shmat");
        exit(1);
    }

    shm_ptr[0] = 0;
    srand(time(NULL));

    while (1)
    {
        int count = rand() % MAX_NUMBERS + 1;
        int *numbers = malloc(count * sizeof(int));

        for (int i = 0; i < count; i++)
        {
            numbers[i] = rand() % 100;
        }
        memset(&shm_ptr[1], '\0', SHM_SIZE-1);
        memcpy(&shm_ptr[1], numbers, count * sizeof(int));
        shm_ptr[0]++;

        pid_t pid = fork();
        if (pid == 0)
        {
            int min = numbers[0];
            int max = numbers[0];

            for (int i = 1; i < count; i++)
            {
                min = (numbers[i] < min) ? numbers[i] : min;
                max = (numbers[i] > max) ? numbers[i] : max;
            }

            shm_ptr[count + 1] = min;
            shm_ptr[count + 2] = max;

            free(numbers);
            exit(0);
        }
        else if (pid > 0)
        {
            free(numbers);
            wait(NULL);

            int min = shm_ptr[count + 1];
            int max = shm_ptr[count + 2];
            printf("Набор %d: Минимум = %d, Максимум = %d\n", shm_ptr[0], min, max);
        }
        else
        {
            perror("fork");
            exit(1);
        }
        sleep(2);
    }

    return 0;
}
