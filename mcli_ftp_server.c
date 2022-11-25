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

void main()   /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, struct_size;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAX];

    pid_t childpid;
    struct_size = sizeof(cliaddr);

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

    // clearing previous server info
    memset(&servaddr, '\0', sizeof(servaddr));
    //  bzero(&servaddr, sizeof(servaddr));

    // port and IP assign to server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // binding() srever to socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("Binding unsuccessfull..\n");
        exit(1);
    }
    else
    {
        printf("Binding successfull..\n");
    }

    // listen()
    if (listen(sockfd, 10) != 0)
    {
        printf("Server listening failed..\n");
    }
    else
    {
        printf("Server is listening...\n");
    }

    // accept()
    while (1)
    {
        connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &struct_size);
        if (connfd < 0)
        {
            printf("Server failed to connect the client..\n");
            exit(1);
        }
        else
        {
            printf("Connection accepted from %s: %d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        }

        if ((childpid = fork()) == 0)
        {
            close(sockfd); // why?
            while (1)
            {
                recv(connfd, buffer, MAX, 0); //***************
                if (strcmp(buffer, "exit") == 0)
                {
                    printf("Disconnecting form %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    exit(1);
                }
                else
                {
                    // printf("Client Message: %s\n", buffer);
                    // send(connfd, buffer, strlen(buffer), 0);
                    // bzero(buffer, sizeof(buffer));

                    printf("Message from client %d:%s\n", ntohs(cliaddr.sin_port), buffer);
                    bzero(buffer, sizeof(buffer));

                    printf("Enter a response to client %d:: ", ntohs(cliaddr.sin_port));
                    gets(buffer);
                    send(connfd, buffer, strlen(buffer), 0); // ********************// ssize_t send(int socket, const void *buffer, size_t length, int flags)
                    // read(connfd, buff, sizeof(buff));
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }

    close(connfd);
}
