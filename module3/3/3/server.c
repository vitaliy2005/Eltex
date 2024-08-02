#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512
#define MAX_CLIENTS 10

typedef struct
{
    long msg_type;
    char text[MAX_TEXT];
    int client_id;
} message_buf;

int main()
{
    key_t key;
    int32_t msgid;
    message_buf message;
    int32_t pids[MAX_CLIENTS] = {0};
    msgid = msgget(666, 0666 | IPC_CREAT);

    int client_count = 0;

    printf("Chat server started...\n");
    int32_t flag = 1;
    while (1)
    {
        // break;

        msgrcv(msgid, &message, sizeof(message.text) + sizeof(int), 2, 0);

        for (int32_t i = 0; i < client_count; i++)
        {
            if (message.client_id == pids[i])
            {
                printf("%d\n", pids[i]);
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            pids[client_count++] = message.client_id;
        }
        else
        {
            flag = 1;
        }
        char msg_with_id[MAX_TEXT + 20];
        sprintf(msg_with_id, "Client %d: %s", message.client_id, message.text);
        printf("%s\n", msg_with_id);
        int32_t temp_id_cliemt = message.client_id;
        for (int i = 0; i < client_count; i++)
        {
            if(pids[i] == temp_id_cliemt)
            {
                continue;
            }
            message.msg_type = pids[i];
            strcpy(message.text, msg_with_id);
            msgsnd(msgid, &message, sizeof(message.text) + sizeof(int), 0);
        }
    }

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
