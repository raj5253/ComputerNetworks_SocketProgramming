
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h> //for time_t
#define PORT 5555

int main(int argc, char const *argv[])  /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, struct_size, connect_result;
    struct sockaddr_in servaddr, cliaddr;

    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket cretion failed..\n");
        exit(0);
    }
    else
    {
        printf("Socket created sucessfully..\n");
        printf("Socket created with socket_no : %d\n", sockfd);
    }

    // clearing previous server info
    bzero(&servaddr, sizeof(servaddr));

    // port and IP assign to server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    struct_size = sizeof(cliaddr);

    connect(sockfd, (struct sockaddr *)&servaddr, struct_size);
    printf("connection result: %d\n", connect_result);

    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("data from server: %s\n", buffer);

    return 0;
}
