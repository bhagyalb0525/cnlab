#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int clients[10];
int count = 0;

int main()
{
    int sockfd, newsockfd;

    struct sockaddr_in server, client;

    socklen_t addr_size;

    char buffer[1000];

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Fill server structure
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(sockfd,
        (struct sockaddr*)&server,
        sizeof(server));

    // Listen
    listen(sockfd, 5);

    printf("Chat server waiting...\n");

    while(1)
    {
        addr_size = sizeof(client);

        // Accept client
        newsockfd = accept(sockfd,
                          (struct sockaddr*)&client,
                          &addr_size);

        // Store client socket
        clients[count] = newsockfd;
        count++;

        printf("New client %d connected\n",count);

        // Create child process
        if(fork() == 0)
        {
            while(1)
            {
                // Receive message
                recv(newsockfd,
                    buffer,
                    sizeof(buffer),
                    0);

                printf("Client %d says: %s\n",count, buffer);

                // Send to all clients
                for(int i = 0; i < count; i++)
                {
                    send(clients[i],
                        buffer,
                        strlen(buffer),
                        0);
                }
            }
        }

        close(newsockfd);
    }

    close(sockfd);

    return 0;
}
