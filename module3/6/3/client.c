#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

#define SERVER_IP "127.0.0.1" // IP-адрес сервера
#define SERVER_PORT 666      // Порт сервера
#define BUFFER_SIZE 65536      // Размер буфера


int main()
{
    int sock;
    struct sockaddr_in server_addr;
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);


    char message[] = "asd";

    struct udphdr *udp_header = (struct udphdr *)buffer;
    udp_header->source = htons(12345);
    udp_header->dest = htons(SERVER_PORT);
    udp_header->len = htons(strlen(message));
    udp_header->check = 0;

    int payload_size = sizeof(buffer) - sizeof(struct udphdr);
    unsigned char *data = buffer + sizeof(struct udphdr);
    for (int i = 0; i < strlen(message); i++)
    {
        data[i] = message[i];
    }

    if (sendto(sock, buffer, sizeof(struct udphdr) + strlen(message), 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the server\n");

    close(sock);
    return 0;
}
