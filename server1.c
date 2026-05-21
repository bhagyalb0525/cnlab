#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 8081
#define MAX 10

int clients[MAX];
int count = 0;

void broadcast(char *msg, int sender)
{
    for(int i=0;i<count;i++)
    {
        if(clients[i] != sender)
        {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(server_fd < 0)
    {
        printf("socket error\n");
        exit(1);
    }

    printf("server socket created successfully\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        printf("binding failed\n");
        exit(1);
    }

    printf("binding successful\n");

    listen(server_fd,5);
    printf("server listening on port %d\n",PORT);

    while(1)
    {
        len = sizeof(client);
        client_fd = accept(server_fd,(struct sockaddr*)&client,&len);

        clients[count++] = client_fd;

        printf("client %d connected\n",count);

        if(fork() == 0)
        {
            // CHILD PROCESS HANDLES ONE CLIENT
            while(1)
            {
                memset(buffer,0,sizeof(buffer));

                int n = recv(client_fd,buffer,sizeof(buffer),0);

                if(n <= 0)
                {
                    printf("client disconnected\n");
                    close(client_fd);
                    exit(0);
                }

                printf("client: %s\n",buffer);

                broadcast(buffer, client_fd);
            }
        }
    }

    close(server_fd);
    return 0;
}
