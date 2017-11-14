#include "netutils.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <glib.h>

int get_local_ip(const char* pszName, char* pszIP, int nMaxLenth)
{
    g_return_val_if_fail((pszName != NULL), 1);
    g_return_val_if_fail((pszIP != NULL), 1);
    g_return_val_if_fail((nMaxLenth >= 16), 1);

    int n;
    struct ifreq ifr;

    n = socket(AF_INET, SOCK_DGRAM, 0);
    //Type of address to retrieve - IPv4 IP address
    ifr.ifr_addr.sa_family = AF_INET;
    //Copy the interface name in the ifreq structure
    strncpy(ifr.ifr_name , pszName , strlen(pszName));
    ioctl(n, SIOCGIFADDR, &ifr);
    close(n);
    //display result
//    printf("IP Address is %s - %s\n" , pszName , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
    char* _pszIP = inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr);
    strncpy(pszIP, _pszIP, strlen(_pszIP));

    return 0;
}