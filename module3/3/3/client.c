#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512

typedef struct
{
    long msg_type;
    char text[MAX_TEXT];
    int client_id;
} message_buf;

int main() {
    key_t key;
    int32_t msgid;
    message_buf message;

    msgid = msgget(666, 0666 | IPC_CREAT);

    message.client_id = (int32_t)getpid();
    printf("Client %d started...\n", message.client_id);

    message.msg_type = 2;
    msgsnd(msgid, &message, sizeof(message.text) + sizeof(int), 0);

    while (1)
    {
        printf("Enter message: ");
        fgets(message.text, sizeof(message.text), stdin);

        message.text[strcspn(message.text, "\n")] = 0;

        message.msg_type = 2;
        msgsnd(msgid, &message, sizeof(message.text) + sizeof(int), 0);

        msgrcv(msgid, &message, sizeof(message.text) + sizeof(int), (int32_t)getpid(), 0);
        printf("Received: %s\n", message.text);
    }

    return 0;
}
