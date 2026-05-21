#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
    int sockfd;

    struct sockaddr_in server;

    char buffer[1000];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Fill server structure
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd,
           (struct sockaddr*)&server,
           sizeof(server));

    printf("Connected to chat server\n");

    // Create child process
    if(fork() == 0)
    {
        // Receive messages
        while(1)
        {
            recv(sockfd,
                buffer,
                sizeof(buffer),
                0);

            printf("\nMessage: %s\n", buffer);
        }
    }

    // Send messages
    while(1)
    {
        fgets(buffer, sizeof(buffer), stdin);

        send(sockfd,
            buffer,
            strlen(buffer),
            0);
    }

    close(sockfd);

    return 0;
}
