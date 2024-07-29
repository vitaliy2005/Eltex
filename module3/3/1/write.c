#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define MAX_LENGHT_DATA 64
#define MSG_NAME "msg"

struct message
{
    long msg_type;
    char data[MAX_LENGHT_DATA];
};

int main()
{
    key_t key = ftok(MSG_NAME, 64);
    int32_t msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid < 0)
    {
        perror("msgget ошибка");
        return 1;
    }

    struct message msg;
    int32_t randomInt;
    srand(time(0));

    for (int i = 1; i < 10; i++)
    {
        msg.msg_type = i;
        randomInt = rand() % 100;
        sprintf(msg.data, "%d", randomInt);
        msgsnd(msgid, &msg, sizeof(msg.data), 0);
        printf("Отправлено: %s\n", msg.data);
    }
    msg.msg_type = 255;
    randomInt = rand() % 100;
    sprintf(msg.data, "%d", randomInt);

    msgsnd(msgid, &msg, sizeof(msg.data), 0);
    printf("Отправлено*: %s\n", msg.data);

    return 0;
}
