#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>


#define MAX_LENGTH_DATA 512
#define QUEUE_NAME "/msg_queue2"

int main()
{
    mqd_t mq;
    int32_t randomInt;
    uint32_t prio;
    char data[MAX_LENGTH_DATA];
    strcpy(data, "");
    srand(time(0));
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_LENGTH_DATA;
    attr.mq_curmsgs = 0;
    if ((mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR , 0600, &attr)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        return -1;
    }

    for (int i = 1; i < 10; i++)
    {
        prio = i;
        randomInt = rand() % 100;
        snprintf(data, sizeof(data), "%d", randomInt);
        data[strlen(data)] = '\0';
        if (mq_send(mq, data, strlen(data), 0) == -1)
        {
            perror("mq_send ошибка");
            return 1;
        }
        printf("Отправлено: %s %lu\n", data, strlen(data));
        sleep(2);
    }

    prio = 255;
    randomInt = rand() % 100;
    snprintf(data, sizeof(data), "%d", randomInt);
    if (mq_send(mq, data, strlen(data), prio) == -1)
    {
        perror("mq_send ошибка");
        return 1;
    }
    printf("Отправлено*: %s\n", data);

    if (mq_close(mq) == -1)
    {
        perror("mq_close ошибка");
    }
    if (mq_unlink(QUEUE_NAME) == -1)
    {
        perror("mq_unlink ошибка");
    }
    return 0;
}
