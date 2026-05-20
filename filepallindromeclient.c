#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 8000

int main()
{
    int sockfd,newsockfd;
    struct sockaddr_in server;
    socklen_t len;
    char filename[800];
    char buffer[800];
    FILE *fp;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=inet_addr("127.0.0.1");
     server.sin_port=htons(PORT);

     printf("socket created successfully\n");

     connect(sockfd,(struct sockaddr *)&server,sizeof(server));

     printf("enter filename ");
     scanf("%s",filename);

     send(sockfd,filename,strlen(filename),0);

     int n=recv(sockfd,buffer,sizeof(buffer),0);
     buffer[n]='\0';
     printf("\n%s\n",buffer);

     close(sockfd);
     return 0;
}
