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
    FILE *fp2;
    char words[1000];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
     server.sin_family=AF_INET;
     server.sin_addr.s_addr=INADDR_ANY;
     server.sin_port=htons(PORT);

     printf("socket created successfully\n");

     bind(sockfd,(struct sockaddr *)&server,sizeof(server));

     listen(sockfd,5);

     printf("server waiting on port 8000\n");

        len=sizeof(client);
        newsockfd=accept(sockfd,(struct sockaddr *)&client,&len);

            int n=recv(newsockfd,filename,sizeof(filename),0);
            filename[n]='\0';
            printf("filename received:%s\n",filename);
             
            char pallindrome[800]="";
            fp=fopen(filename,"r");
            fp2=fopen("pallindrome.txt","w");
            if(fp==NULL)
{
           printf("file not found\n");
}
else{
            while(fscanf(fp,"%s",words)!=EOF)
            {
                int i,lens,pal=1;
                lens=strlen(words);
                for(i=0;i<=lens/2;i++)
                {
                    if(words[i]!=words[lens-i-1])
                    {
                        pal=0;
                        break;
                    }
                }
                if(pal)
                {
                    fprintf(fp2,"%s\n",words);
                }
            }
                fclose(fp2);

                fp2=fopen("pallindrome.txt","r");
                while(fgets(buffer,sizeof(buffer),fp2)!=NULL)
                {
                    strcat(pallindrome,buffer);
                }
                send(newsockfd,pallindrome,strlen(pallindrome),0);
                printf("pallindrome words sent");

                fclose(fp2);
                fclose(fp);
                close(newsockfd);
                close(sockfd);
                return 0;

            }
        }
