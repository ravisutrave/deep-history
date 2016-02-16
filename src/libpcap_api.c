#include<pcap.h>
#include "libpcap_api.h"

    /*Initialize network device name got as input
     * The name can be:
     * if offline_capture is 0
     *     "any" -> To capture packets on all interfaces
     *     "<some interface name>" -> Either known interface or the name got from pcap_lookupdev 
     *  if offlince_capture is 1
     *      Path of pcap file */
int
init_interface(char * net_device, unsigned char offline_capture, packet_callback packet_listener) 
{
    /*error buffer for libpcap API's*/
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *p_handle = NULL; 
    struct bpf_program filter_pgm;
    char filter_exp[] = "tcp";
    if(!offline_capture){
        p_handle = pcap_open_live(net_device, SNAP_LEN, 1, 1000, errbuf);
    } else {
        p_handle = pcap_open_offline(net_device,errbuf);
    }
    if(p_handle == NULL){
        perror("pcap_open_live failed");
        return 0;
    }

    /* compile filter expression */
    if (pcap_compile(p_handle, &filter_pgm, filter_exp, 0, PCAP_NETMASK_UNKNOWN) == -1) {
        perror("Could not compile filter!!");
        return 0;
    }

    /* apply the compiled filter */
    if (pcap_setfilter(p_handle, &filter_pgm) == -1) {
        perror("pcap_setfilter failed");
        return 0;
    }

    pcap_loop(p_handle, 0, packet_listener, NULL);
    pcap_freecode(&filter_pgm);
    pcap_close(p_handle);
    return 1;
}

