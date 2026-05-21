#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 8081

int main()
{
    int sock;
    struct sockaddr_in server;
    char msg[1024], buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        printf("socket error\n");
        exit(1);
    }

    printf("socket created successfully\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if(connect(sock,(struct sockaddr*)&server,sizeof(server)) < 0)
    {
        printf("connection failed\n");
        exit(1);
    }

    printf("connected to server\n");

    if(fork() == 0)
    {
        // CHILD → RECEIVE
        while(1)
        {
            memset(buffer,0,sizeof(buffer));
            recv(sock,buffer,sizeof(buffer),0);
            printf("%s\n",buffer);
        }
    }
    else
    {
        // PARENT → SEND
        while(1)
        {
            fgets(msg,sizeof(msg),stdin);
            send(sock,msg,strlen(msg),0);
        }
    }

    close(sock);
    return 0;
}
