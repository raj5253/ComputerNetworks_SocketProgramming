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

int main()        /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, server_struct_size, n;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[MAX], client_message[MAX];

    FILE *ftr;

    server_struct_size = sizeof(servaddr);

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

    // send file data to server
    bzero(client_message, sizeof(client_message));
    // bzero(client_message, MAX);
    ftr = fopen("clfile.txt", "r");

    n = 0;
    while ((client_message[n++] = getc(ftr)) != EOF)
        ;
    client_message[--n] = '\0'; // since  n was already incremented in while loop.
    fclose(ftr);

    if (sendto(sockfd, client_message, strlen(client_message), 0, (struct sockaddr *)&servaddr, server_struct_size) < 0)
    {
        printf("Couldn't send message to server\n");
    }

    // Response received from server
    if (recvfrom(sockfd, server_message, sizeof(server_message), 0, (struct sockaddr *)&servaddr, &server_struct_size) < 0)
    {
        printf("Couldn't receive message from server\n");
    }
    else
        printf("Mesg from server: %s\n", server_message);

    // close the socket
    close(sockfd);

    return 0;
}