#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int ipv4(char* ip)
{
    char buf[strlen(ip)];
    int32_t j = 0;
    for (int32_t i = 0; i < strlen(ip); i++)
        if(ip[i] != '.') buf[j++] = ip[i];
    return atoi(buf);
}


int main(int argc, char *argv[])
{

    printf("%d\n", ipv4("255.255.34.0"));



    // if (argc != 4) {
    //     printf("Usage: %s gateway_ip subnet_mask num_packets\n", argv[0]);
    //     return 1;
    // }

    // struct in_addr gateway, subnet_mask;
    // uint32_t gateway_ip, subnet_mask_val, ip;
    // int num_packets = atoi(argv[3]);
    // int same_subnet_count = 0, diff_subnet_count = 0;

    // if (inet_pton(AF_INET, argv[1], &gateway) == 0 || inet_pton(AF_INET, argv[2], &subnet_mask) == 0) {
    //     printf("Invalid IP or subnet mask\n");
    //     return 1;
    // }

    // gateway_ip = ntohl(gateway.s_addr);
    // subnet_mask_val = ntohl(subnet_mask.s_addr);

    // srand(time(NULL));

    // for (int i = 0; i < num_packets; i++)
    // {
    //     ip = htonl((gateway_ip & subnet_mask_val) | (rand() & subnet_mask_val));
    //     if ((ip & subnet_mask_val) == (gateway_ip & subnet_mask_val))
    //     {
    //         same_subnet_count++;
    //     }
    //     else
    //     {
    //         diff_subnet_count++;
    //     }
    // }

    // printf("Packets within the subnet: %d (%.2f%%)\n", same_subnet_count, (float)same_subnet_count / num_packets * 100);
    // printf("Packets outside the subnet: %d (%.2f%%)\n", diff_subnet_count, (float)diff_subnet_count / num_packets * 100);

    return 0;
}
