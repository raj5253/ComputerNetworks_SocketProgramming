#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 1024
#define PORT 5555

int main()         /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, server_struct_len, n;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[MAX], client_message[MAX];

    server_struct_len = sizeof(servaddr);

    // clear the buffers
    memset(server_message, 0, sizeof(server_message));
    memset(client_message, 0, sizeof(client_message));

    // socket creation for client
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    // set port and IP
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // providing ip add manually
    servaddr.sin_port = htons(PORT);

    // Get input from user(as cilient)
    printf("Enter a mesage for server: ");
    gets(client_message);

    // send mesage to server
    if (sendto(sockfd, client_message, strlen(client_message), 0, (struct sockaddr *)&servaddr, server_struct_len) < 0)
    {
        printf("Couldn't send message to server\n");
    }

    // Response received from server
    if (recvfrom(sockfd, server_message, sizeof(server_message), 0, (struct sockaddr *)&servaddr, &server_struct_len) < 0)
    {
        printf("Couldn't receive message from server\n");
    }

    printf("Mesg from server: %s\n", server_message);

    // close the socket
    close(sockfd);

    return 0;
}