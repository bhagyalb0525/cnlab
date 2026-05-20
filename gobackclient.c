#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define PORT 8000

int main()
{
    int sockfd;

    socklen_t len;

    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("socket creation failed\n");
        exit(1);
    }

    printf("socket created\n");

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    int frames, window;

    printf("enter number of frames : ");
    scanf("%d", &frames);

    printf("enter window size : ");
    scanf("%d", &window);

    /*
       timeout setting
    */

    struct timeval tv;

    tv.tv_sec = 3;
    tv.tv_usec = 0;

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,
    (const char *)&tv, sizeof(tv));

    len = sizeof(server);

    int base = 1;
    int i;
    int ack;

    while(base <= frames)
    {
        /*
           send window frames
        */

        for(i = base; i < base + window && i <= frames; i++)
        {
            printf("sending frame %d\n", i);

            sendto(sockfd, &i, sizeof(i), 0,
            (struct sockaddr *)&server, sizeof(server));
        }

        /*
           receive ACKs
        */

        for(i = base; i < base + window && i <= frames; i++)
        {
            if(recvfrom(sockfd, &ack, sizeof(ack), 0,
            (struct sockaddr *)&server, &len) < 0)
            {
                printf("timeout for frame %d\n", i);

                printf("go back to frame %d\n", i);

                break;
            }

            else
            {
                printf("ack received for frame %d\n", ack);
            }
        }

        /*
           slide window
        */

        base = i;
    }

    close(sockfd);

    return 0;
}
