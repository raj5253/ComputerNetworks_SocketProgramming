
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

int main(int argc, char const *argv[]) /*Author: SATYAM RAJ : rajsatyam8532@yahoo.com*/
{
    int sockfd, connfd, struct_size, bind_result, listen_result;
    struct sockaddr_in servaddr, cliaddr;

    char buffer[1024];

    time_t current_time;
    time(&current_time);

    int count_client = 0;

    sockfd = socket(AF_INET,SOCK_DGRAM , 0); // an integer
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

    // binding
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)) // 0 when success
    {
        printf("server binding unsuccesfull..\n");
        exit(1);
    }
    else
    {
        printf("Server binding successfull..\n");
    }

    struct_size = sizeof(cliaddr);

    while (1)
    {
        count_client++;
        printf("\n");

        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&cliaddr, &struct_size);
        time(&current_time);

        printf("\nClient %d has requested for time at %s", count_client, ctime(&current_time));

        time(&current_time);
        sendto(sockfd, ctime(&current_time), 1024, 0, (struct sockaddr *)&cliaddr, struct_size);
    }

    return 0;
}
