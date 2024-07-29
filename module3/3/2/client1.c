#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>
#include <string.h>


#define MAX_LENGHT_DATA 64
#define MSG_NAME_SENDER "msg2"
#define MSG_NAME_RECEIVER "msg1"


struct message
{
    long msg_type;
    char data[MAX_LENGHT_DATA];
};

int main()
{
    key_t key1 = ftok(MSG_NAME_SENDER, 64);
    key_t key2 = ftok(MSG_NAME_RECEIVER, 65);

    int msgid1 = msgget(key1, 0666 | IPC_CREAT);
    int msgid2 = msgget(key2, 0666 | IPC_CREAT);



    if ((msgid1 < 0) && (msgid2 < 0))
    {
        perror("msgget ошибка");
        return 1;
    }

    struct message msg;
    char randomInt[1] = "w";
    srand(time(0));
    msg.msg_type = 1;

    for (int i = 1; i < 10; i++)
    {
        strcat(msg.data, randomInt);
        msgsnd(msgid2, &msg, sizeof(msg.data), 0);
        printf("Отправлено: %s\n", msg.data);
        sleep(1);

        if (msgrcv(msgid1, &msg, sizeof(msg.data), 0, 0) < 0)
        {
            perror("msgrcv ошибка");
            return 1;
        }
        printf("Получено: %s\n", msg.data);
    }


    msgctl(msgid1, IPC_RMID, NULL);
    msgctl(msgid2, IPC_RMID, NULL);
    return 0;
}
