#ifndef LIBPCAP_API_H
#define LIBPCAP_API_H
#define TRUE 1
#define FALSE 0
#define SNAP_LEN 1518
typedef void (*packet_callback)(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);
int init_interface(char * net_device, unsigned char offline_capture, packet_callback packet_listener) ;
#endif
