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
    struct sockaddr_in server,client;
    socklen_t len;
    char filename[1000];
    char buffer[800];
    FILE *fp;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(PORT);

     printf("socket created successfully\n");

     bind(sockfd,(struct sockaddr *)&server,sizeof(server));

     listen(sockfd,5);

     printf("server waiting on port 8000\n");

     while(1)
     {
        len=sizeof(client);
        newsockfd=accept(sockfd,(struct sockaddr *)&client,&len);

        if(fork()==0)
        {
            int n=recv(newsockfd,filename,sizeof(filename),0);
            filename[n]='\0';
            printf("filename received:%s\n",filename);
             
            char filecontent[800]="";
            fp=fopen(filename,"r");

            if(fp==NULL)
{
    sprintf(buffer,"File not found\nProcess id:%d",getpid());

    send(newsockfd,buffer,strlen(buffer),0);

    close(newsockfd);

    exit(0);
}
else{
            while(fgets(buffer,sizeof(buffer),fp)!=NULL)
            {
                    strcat(filecontent,buffer);
            }

            sprintf(buffer,"contents of file:%sprocess id:%d\n",filecontent,getpid());
            send(newsockfd,buffer,strlen(buffer),0);
            printf("content send to client\n");

            fclose(fp);
        }
            close(newsockfd);
            exit(0);
    }
    close(newsockfd);
    }
        close(sockfd);
     
     return 0;

}
