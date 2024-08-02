#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h> // Для работы с IP заголовками
#include <netinet/udp.h> // Для работы с TCP заголовками
#include <string.h>

#define SNAP_LEN 65535

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    FILE *dump_file = (FILE *)args;
    fwrite(packet, header->len, 1, dump_file);
    struct ip *ip_header = (struct ip*)(packet + 14);
    struct udphdr *udp_header = (struct udphdr*)(packet + 14 + (ip_header->ip_hl * 4));

    printf("Captured a packet:\n");
    printf("Source IP: %s\n", inet_ntoa(ip_header->ip_src));
    printf("Destination IP: %s\n", inet_ntoa(ip_header->ip_dst));
    printf("Source Port: %d\n", ntohs(udp_header->source));
    printf("Destination Port: %d\n", ntohs(udp_header->dest));
    printf("Packet Length: %d bytes\n", header->len);
    printf("--------------------------------------\n");
}

int main(int argc, char *argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    char *device = "lo";

    handle = pcap_open_live(device, SNAP_LEN, 1, 1000, errbuf);
    if (handle == NULL)
    {
        fprintf(stderr, "Could not open device %s: %s\n", device, errbuf);
        return EXIT_FAILURE;
    }
    printf("Listening on device: %s\n", device);

    struct bpf_program fp;
    char filter_exp[] = "udp port 666";

    if (pcap_compile(handle, &fp, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1)
    {
        fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    if (pcap_setfilter(handle, &fp) == -1)
    {
        fprintf(stderr, "Could not install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    FILE* dump_file = fopen("packet_dump.bin", "wb");
    if (dump_file == NULL)
    {
        perror("Failed to open dump file");
        return 2;
    }

    pcap_loop(handle, 0, packet_handler, (u_char *)dump_file);

    fclose(dump_file);
    pcap_close(handle);

    return EXIT_SUCCESS;
}
