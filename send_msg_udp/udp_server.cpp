#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    // Create socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Config server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    //  Bind socket with address
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    std::cout << "UDP Server is listening on port " << PORT << "...\n";

    // loop to receive data
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                               (struct sockaddr *)&clientAddr, &addr_len);
        if (len < 0) {
            perror("recvfrom error");
            break;
        }

        buffer[len] = '\0';
        std::cout << "Receive from  client: " << buffer << std::endl;

        // Send feedback to client
        std::string reply = "Received: " + std::string(buffer);
        sendto(sockfd, reply.c_str(), reply.size(), 0,
               (const struct sockaddr *)&clientAddr, addr_len);
    }

    close(sockfd);
    return 0;
}
