#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 1000
#define PORT 7777

void client(int sockfd)/*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, sizeof(buff)); // memset can be used instead.

        printf("Enter a string: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff)); // after sending it to server scoket, clear the buffer on client side

        // Receiving resonise from server
        read(sockfd, buff, sizeof(buff));
        printf("From  server : %s\n", buff);

        if (strncmp("exit", buff, 4) == 0)
        {
            printf("client Exit...\n");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd, struct_len;
    struct sockaddr_in servaddr, cliaddr;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket ceation failed..\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    // add port and IP to server
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // connect to client the server

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("Connection to the server failed..\n");
        exit(0);
    }
    else
    {
        printf("Connected to the server...\n");
    }

    client(sockfd);

    close(sockfd);
}
