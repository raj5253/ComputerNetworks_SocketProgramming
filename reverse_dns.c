#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>   

/*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/

static int convert4(struct sockaddr_in *servaddr, const char *buffer)
{
    return inet_pton(servaddr->sin_family = AF_INET, buffer, &servaddr->sin_addr);
}

// int inet_pton(int af, const char *__restrict__ src, void *__restrict__ dst);

static int convert6(struct sockaddr_in6 *servaddr, const char *buffer)
{
    return inet_pton(servaddr->sin6_family = AF_INET, buffer, &servaddr->sin6_addr);
}

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [IP]\nE.g. %s 10.32.129.77\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    // printf("Enter an IPv4 addr and IPv6 addr:\n");

    union
    {
        struct sockaddr servaddr;
        struct sockaddr_in servaddr4;
        struct sockaddr_in6 servaddr6;
        struct sockaddr_storage servaddr_store;
    } addr;

    if (convert4(&addr.servaddr4, argv[1]) != 1 && convert6(&addr.servaddr6, argv[1]) != 1)
    {
        fprintf(stderr, "%s: not a valid IP address.\n", argv[1]);
        return EXIT_FAILURE;
    }

    char node[NI_MAXHOST];
    int res = getnameinfo(&addr.servaddr, sizeof(addr), node, sizeof(node), NULL, 0, NI_NAMEREQD);

    if (res)
    {
        fprintf(stderr, "%s: %s\n", argv[1], gai_strerror(res));
        return EXIT_FAILURE;
    }

    puts(node);
    return 0;
}