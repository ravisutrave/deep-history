#include <stdio.h>
#include<pcap.h>
#include "libpcap_api.h"

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) 
{
    (void )args;
    (void ) header;
    (void ) packet;
    printf("Got a packet\n");
}
int main(int argc, char *argv[]) {
    if(argc == 1) {
        /*Print usage TODO*/
    } else if (argc == 2) {
        init_interface(argv[1], 1, got_packet);
    } else {
        init_interface("any", 0, got_packet);
    }
    printf("Hello World\n");
    return 0;
}
