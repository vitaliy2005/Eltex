#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <string.h>

#define BUFFER_SIZE 65536


void process_packet(unsigned char *buff, int size)
{
    // struct iphdr *iph = (struct iphdr *) buff;
    // unsigned short iphdrlen = iph->ihl * 4;
    struct udphdr *udph = (struct udphdr *) (buff);


    printf("Data (Payload): ");
    int payload_size = size - sizeof(struct udphdr);
    unsigned char *data = buff + sizeof(struct udphdr);

    unsigned short source_port = ntohs(udph->source);
    unsigned short dest_port = ntohs(udph->dest);

    if (source_port == 666 || dest_port == 666)
    {
        for (int i = 0; i < size; i++)
        {
            printf("%c ", buff[i]);
        }
        printf("\n\n");
    }


}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Использование: %s <номер порта>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
   struct sockaddr_in server_addr, client_addr;
   socklen_t addr_len = sizeof(client_addr);
    unsigned char *buffer = (unsigned char *)malloc(BUFFER_SIZE);

    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) < 0)
    {
        perror("Ошибка при создании сокета");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(666);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (recv_len < 0)
        {
            perror("Ошибка при получении данных");
            continue;
        }

        buffer[recv_len] = '\0';
        printf("%s", buffer);
        process_packet(buffer, recv_len);
    }

    free(buffer);
    close(sockfd);
    return 0;
}
