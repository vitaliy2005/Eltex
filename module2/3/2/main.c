#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ipv4(char ip[])
{
    char* buf;
    uint8_t bit = 0;
    int32_t ipBin = 0;

    buf = strtok(strdup(ip), ".");

    while (buf != NULL)
    {
        bit = (uint8_t)atoi(buf);
        ipBin |=  bit;
        ipBin = ipBin << 8;
        buf = strtok(NULL, ".");
    }
    return ipBin;
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (argc != 4) {
        printf("Параметры: %s gateway_ip subnet_mask num_packets\n", argv[0]);
        return 1;
    }

    uint32_t gateway = ipv4(argv[1]), subnet_mask = ipv4(argv[2]);
    int32_t num_packets = atoi(argv[3]);
    int same_subnet_count = 0, diff_subnet_count = 0;
    int32_t ip;

    for (int i = 0; i < num_packets; i++)
    {
        ip = (gateway & subnet_mask) | (rand() & subnet_mask);
        if ((ip & subnet_mask) == (gateway & subnet_mask))
        {
            same_subnet_count++;
        }
        else
        {
            diff_subnet_count++;
        }
    }

    printf("Пакеты внутри сети: %d (%.2f%%)\n", same_subnet_count, (float)same_subnet_count / num_packets * 100);
    printf("Пакеты отправлены во внешную сеть: %d (%.2f%%)\n", diff_subnet_count, (float)diff_subnet_count / num_packets * 100);

    return 0;
}
