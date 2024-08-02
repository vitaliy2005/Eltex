#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_NAME "/msg_queue2"
#define MAX_LENGTH_DATA 1024


int main()
{
    mqd_t mq;
    uint32_t prio;
    char data[MAX_LENGTH_DATA+10];
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_LENGTH_DATA*2;
    attr.mq_curmsgs = 0;

    mq = mq_open(QUEUE_NAME, O_RDONLY, 0644, &attr);
    if (mq == (mqd_t)-1)
    {
        perror("mq_open ошибка");
        return 1;
    }

    while (1)
    {
        strcpy(data, "");
        if (mq_receive(mq, data, MAX_LENGTH_DATA, &prio) != -1)
        {
            int a;
            if (prio == 255)
            {
                printf("Получено: %d\n", a);
                printf("Получено сообщение с типом 255\n");
                break;
            }
            sscanf(data, "%d", &a);

            printf("Получено: %d\n", a);
        }
        else
        {
            perror("mq_receive ошибка");
            break;
        }
        sleep(1);
    }

    if (mq_close(mq) == -1)
    {
        perror("mq_close ошибка");
    }

    return 0;
}
