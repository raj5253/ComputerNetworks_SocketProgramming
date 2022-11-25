#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX 1024
#define PORT 5555

void main()  /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, struct_len;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAX];

    // pid_t childpid;
    struct_len = sizeof(cliaddr);

    // socket creation
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket creation unsuccessfull..\n");
        exit(0);
    }
    else
    {
        printf("Socket creation successfull..\n");
    }

    // clearing previous server info //bzero(&servaddr, sizeof(servaddr));
    memset(&servaddr, '\0', sizeof(servaddr));

    // port and IP assign to server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect()
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Connection to server failed.\n");
        exit(1);
    }
    else
        printf("Connection to server successfull..\n");

    while (1)
    {
        printf("Enter the message for server: ");
        gets(buffer);
        send(sockfd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0)
        {
            close(sockfd);
            printf("Disconnecting form server.\n");
            exit(1);
        }

        if (recv(sockfd, buffer, MAX, 0) < 0)
        {
            printf("Error in receiving message from server\n");
        }
        else
        {
            printf("Message from server: %s\n", buffer);
        }
    }
}
