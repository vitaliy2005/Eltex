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
#include <sys/mman.h>
#include <fcntl.h>

#define SHM_SIZE 1024
#define MAX_NUMBERS 100
#define SHM_NAME "/shm_1"

int *shm_ptr;
int shm_fd;

void handle_sigint(int sig)
{
    close(shm_fd);
    shm_unlink(SHM_NAME);
    printf("\nЗавершение работы. Обработано наборов данных: %d\n", shm_ptr[0]);
    exit(0);
}

int main()
{
    signal(SIGINT, handle_sigint);

    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shm_fd, SHM_SIZE) == -1)
    {
            perror("ftruncate");
            exit(EXIT_FAILURE);
    }

    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
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
