#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define MAX 1024
#define PORT 5555

void func(int confd) /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    char buffer[MAX];
    FILE *ftr;

    bzero(buffer, MAX);
    read(confd, buffer, sizeof(buffer)); // read from socket into buffer.

    printf("From client : %s\n", buffer);

    ftr = fopen("sfile", "w"); // this can be in append mode also.but I don't previous program data.
    fputs(buffer, ftr);
    fclose(ftr);
}

int main()
{
    int sockfd, connfd, struct_len;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation failed..\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)

    {
        printf("socket bind failed....\n");
        exit(0);
    }
    else
    {
        printf("server succesfully binded..\n");
    }

    if (listen(sockfd, 5) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening....\n");
    }

    struct_len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &struct_len);

    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("server is ready to accept the client...\n");
    }

    func(connfd); // pass the connection socket.
    close(sockfd);
}