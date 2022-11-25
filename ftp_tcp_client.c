#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 1024
#define PORT 5555

void func(int sockfd) /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    char buffer[MAX];
    FILE *ftr;
    int n;

    bzero(buffer, sizeof(buffer));
    ftr = fopen("clfile.txt", "r");
    bzero(buffer, MAX);

    n = 0;
    while ((buffer[n++] = getc(ftr)) != EOF)
        ;
    buffer[--n] = '\0'; // since  n was already incremented in while loop.

    write(sockfd, buffer, sizeof(buffer));

    fclose(ftr);
}

int main()
{

    int sockfd, connfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // socket creation

    if (sockfd == -1)
    {
        printf("Socket creation failed..\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr)); // why ? just to clear info of server.

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connect to server failed..\n");
    }
    else
    {
        printf("connected to the server..\n");
    }

    func(sockfd); // we need to connect to server. so provide socketof server.

    close(sockfd);
}
