#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  MAX_LENGHT_DATA 64
#define MSG_NAME "msg"

struct message
{
    long msg_type;
    char data[MAX_LENGHT_DATA];
};

int main()
{
    key_t key = ftok(MSG_NAME, 64);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid < 0)
    {
        perror("msgget ошибка");
        return 1;
    }

    struct message msg;

    while (1)
    {
        if (msgrcv(msgid, &msg, sizeof(msg.data), 0, 0) < 0)
        {
            perror("msgrcv ошибка");
            return 1;
        }

        if (msg.msg_type == 255)
        {
            printf("Получено сообщение с типом 255\n");
            break;
        }

        printf("Received: %s\n", msg.data);
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
