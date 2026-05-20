#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000

int main() {
    int sockfd;
    char buffer[100];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // 1. Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Set up server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket to port
    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("UDP Time Server running on port %d...\n", PORT);

    while (1) {
        // 4. Wait for a message from any client
        recvfrom(sockfd, buffer, sizeof(buffer), 0,
                 (struct sockaddr*)&client, &len);

        printf("Request received: %s\n", buffer);

        // 5. Fork a child process to handle this client
        if (fork() == 0) {
            // --- Inside child process ---

            // 6. Get current system time
            time_t t = time(NULL);
            char *timestr = ctime(&t);

            // 7. Send time back to the client
            sendto(sockfd, timestr, strlen(timestr), 0,
                   (struct sockaddr*)&client, len);

            printf("Time sent to client.\n");
            exit(0); // child exits after serving
        }
        // Parent loop continues to wait for next client
    }

    close(sockfd);
    return 0;
}
