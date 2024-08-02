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
#include <time.h>


#define QUEUE_NAME "/msg_queue2"
#define QUEUE_NAME2 "/msg_queue1"

#define MAX_LENGTH_DATA 512


int main()
{
    char randomInt[1] = "2";
    srand(time(NULL));
    mqd_t mq, mq2;
    uint32_t prio;
    char data[MAX_LENGTH_DATA+10];
    strcpy(data, "");
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
    if ((mq2 = mq_open(QUEUE_NAME2, O_CREAT | O_RDWR , 0600, &attr)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        return -1;
    }
    // mq_unlink(QUEUE_NAME);
    // return 0;

    for (int32_t i = 1; i < 10; i++)
    {
        if (mq_receive(mq, data, MAX_LENGTH_DATA, &prio) != -1) {}
        else
        {
            perror("mq_receive ошибка");
            break;
        }
        sscanf(data, "%s", data);
        printf("Получено: %s\n", data);
        sleep(1);
        strcat(data, randomInt);
        if (mq_send(mq2, data, strlen(data), 0) == -1)
        {
            perror("mq_send ошибка");
            return 1;
        }
    }


    return 0;
}
