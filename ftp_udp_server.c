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
#define SA struct sockaddr
#define PORT 5555

int main()                             /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, client_struct_size, n;
    struct sockaddr_in servaddr, cliaddr;
    char server_message[MAX], client_message[MAX];
    FILE *ftr;

    client_struct_size = sizeof(cliaddr);

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

    // receive client file data:
    if (recvfrom(sockfd, client_message, sizeof(client_message), 0, (struct sockaddr *)&cliaddr, &client_struct_size) < 0)
    {
        printf("Couldn't file message from client\n");
        ftr = fopen("s_udp_file", "w"); // creating a file
        fputs(client_message, ftr);
        fclose(ftr);
    }
    printf("Content of Client file: %s\n", client_message);

    printf("Enter a response for client..\n");
    gets(server_message);
    if (sendto(sockfd, server_message, strlen(server_message), 0, (struct sockaddr *)&cliaddr, client_struct_size) < 0)
    {
        printf("Can't sent response to client\n");
    }

    // close the socket
    close(sockfd);

    return 0;
}