#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 8000

int main()
{
    int sockfd;
    int frame, ack;
    int expected = 1;

    socklen_t len;

    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0)
    {
        printf("socket creation failed\n");
        exit(1);
    }

    printf("socket created\n");

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("binding failed\n");
        exit(1);
    }

    printf("waiting for frames...\n");

    len = sizeof(client);

    int lost = 0;

    while(1)
    {
        recvfrom(sockfd, &frame, sizeof(frame), 0,
        (struct sockaddr *)&client, &len);

        printf("frame received : %d\n", frame);

        /*
           simulate ACK loss only once
        */

        if(frame == 2 && lost == 0)
        {
            printf("ack lost for frame %d\n", frame);

            lost = 1;

            continue;
        }

        /*
           Go-Back-N accepts only expected frame
        */

        if(frame == expected)
        {
            ack = frame;

            sendto(sockfd, &ack, sizeof(ack), 0,
            (struct sockaddr *)&client, len);

            printf("ack sent : %d\n", ack);

            expected++;
        }

        else
        {
            printf("frame %d discarded\n", frame);
        }
    }

    close(sockfd);

    return 0;
}
