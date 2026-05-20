#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000
#define SERVER_IP "127.0.0.1"

int main() {
    int sockfd;
    char buffer[100];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Set server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 3. Send "time?" request to server
    char *msg = "time?";
    sendto(sockfd, msg, strlen(msg), 0,
           (struct sockaddr*)&server, sizeof(server));

    printf("Request sent. Waiting for time...\n");

    // 4. Receive the time from server
    recvfrom(sockfd, buffer, sizeof(buffer), 0,
             (struct sockaddr*)&server, &len);

    printf("Time from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
