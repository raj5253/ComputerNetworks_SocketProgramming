
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

int main(int argc, char const *argv[])          /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, struct_size, bind_result, listen_result;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];

    time_t current_time;
    time(&current_time);

    int count_client = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // an integer
    if (sockfd == -1)
    {
        printf("Socket cretion failed..\n");
        exit(0);
    }
    else
    {
        printf("Socket created sucessfully..\n");
    }

    // clearing previous server info
    bzero(&servaddr, sizeof(servaddr));

    // port and IP assign to server
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    struct_size = sizeof(cliaddr);

    count_client++;
    printf("\n");

    strcpy(buffer, " ");

    sendto(sockfd, buffer, 1024, 0, (struct sockaddr *)&servaddr, struct_size);
    time(&current_time);

    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&servaddr, &struct_size);
    printf("message from server: %s\n", buffer);

    close(sockfd);

    return 0;
}
