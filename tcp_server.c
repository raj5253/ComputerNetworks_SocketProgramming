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

void server(int connfd) /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, MAX); // memset can be used instead.

        read(connfd, buff, sizeof(buff));
        printf("Mesg from client: %s\t to client: ", buff);
        bzero(buff, MAX);

        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        write(connfd, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exit...\n");
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

    // clear the buffer
    bzero(&servaddr, sizeof(servaddr));

    // add port and IP to server
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // binding the socket to the  servaddr(IP)
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Binding failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully bided..\n");
    }

    // make the server passive(start to listen)
    if (listen(sockfd, 5) != 0)
    {
        printf("listen failed...\n");
    }
    else
        printf("Server listening ...\n");

    struct_len = sizeof(servaddr);

    // accept data from client.Make server active
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &struct_len);
    if (connfd < 0)
    {
        printf("Server accept failed...\n");
        exit(0);
    }
    else
        printf("server accepted the client..\n");

    server(connfd);

    close(sockfd);
}
