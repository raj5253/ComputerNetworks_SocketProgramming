
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

    time_t current_time;
    time(&current_time); // no use of this line.

    int count_client = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0); // an int
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

    // binding
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)) // 0 for success
    {
        printf("server binding unsuccesfull..\n");
        exit(1);
    }
    else
    {
        printf("Server binding successfull..\n");
        printf("result of bind: %d\n", bind_result);
    }

    // listen()                                 // -ve value
    if (listen(sockfd, 10) != 0)
    {
        printf("Server listening failed..\n");
    }
    else
    {
        printf("Server is listening...\n");
        printf("Listening result : %d\n", listen_result);
    }

    struct_size = sizeof(cliaddr);

    while (1)
    {
        count_client++;
        printf("\n");
        connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &struct_size);

        printf("Client %d has requested for time at %s\n", count_client, ctime(&current_time));

        send(connfd, ctime(&current_time), 1024, 0);
    }

    return 0;
}

// send(connfd, ctime(&current_time), 1024, 0);  //the diffrence is of the last extra flag only.
// write(connfd, ctime(&current_time), 1024);
