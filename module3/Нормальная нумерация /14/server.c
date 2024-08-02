#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    struct sockaddr_in clients[2];
    int client_count = 0;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&clients[0], 0, sizeof(clients[0]));
    memset(&clients[1], 0, sizeof(clients[1]));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Сервер запущен. Ожидание сообщений...\n");
    char temp[BUFFER_SIZE];
    int n, n2;
    while (1)
    {
        n = recvfrom(sockfd, (char *)temp, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&clients[0], &addr_len);
        temp[n] = '\0';
        n2 = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&clients[1], &addr_len);
        buffer[n2] = '\0';
        printf("%d %d\n", ntohs(clients[0].sin_port), ntohs(clients[1].sin_port));
        sendto(sockfd, temp, n, MSG_CONFIRM, (const struct sockaddr *)&clients[1], addr_len);
        sendto(sockfd, buffer, n2, MSG_CONFIRM, (const struct sockaddr *)&clients[0], addr_len);
    }

    close(sockfd);
    return 0;
}
