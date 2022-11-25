#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 1024
#define SA struct sockaddr
#define PORT 5555

int main()         /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, client_struct_len, n;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[MAX], client_message[MAX];

    client_struct_len = sizeof(cliaddr);

    // clear the buffers
    memset(server_message, 0, sizeof(server_message));
    memset(client_message, 0, sizeof(client_message));

    // socket creation of server
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

    // Binding sever(IP) to the socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) // != 0
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    printf("Listening for incoming messages...\n");

    // receive client message:
    if (recvfrom(sockfd, client_message, sizeof(client_message), 0, (struct sockaddr *)&cliaddr, &client_struct_len) < 0)
    {
        printf("Couldn't receive message from client\n");
    }

    printf("Mesg from Client: %s\n", client_message);

    // Respond to client
    // strcpy(server_message, client_message);
    printf("Enter a mesg for client: ");
    gets(server_message);

    if (sendto(sockfd, server_message, strlen(server_message), 0, (struct sockaddr *)&cliaddr, client_struct_len) < 0)
    {
        printf("Can't sent to client\n");
    }

    // close the socket
    close(sockfd);

    return 0;
}