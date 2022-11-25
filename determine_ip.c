#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

void main()        /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{

    int i;
    char host[80];
    struct hostent *he;
    // struct in_addr addr;

    printf("Enter the host-name : ");
    gets(host);
    he = gethostbyname(host);
    if (he == NULL)
    {
        printf("The address cannot be determined at this time.");
        exit(1);
    }

    printf("Official name is : %s\n", he->h_name);
    printf("IP address: %s\n", inet_ntoa(*(struct in_addr *)he->h_addr));

    // printf("IP address: %s\n", he->h_addr);  //this wont work
}

/*

Entert the host-name: yahoo.com
Official name is : yahoo.com
IP address: 74.6.143.25

*/