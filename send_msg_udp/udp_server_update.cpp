#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    bool clientConnected = false;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Setup server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    std::cout << " UDP Server listening on port " << PORT << "...\n";

    // Thread for receiving data
    std::thread recvThread([&]() {
        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                                   (struct sockaddr *)&clientAddr, &addr_len);
            if (len < 0) {
                perror("recvfrom error");
                break;
            }

            buffer[len] = '\0';
            clientConnected = true;  // client đã gửi -> đã biết địa chỉ
            std::cout << "\n Client: " << buffer << std::endl;
            std::cout << "Server> " << std::flush; // hiện prompt lại
        }
    });

    // Thread for sending data (user input)
    std::thread sendThread([&]() {
        std::string msg;
        while (true) {
            std::cout << "Server> ";
            std::getline(std::cin, msg);
            if (msg == "exit") break;

            if (clientConnected) {
                sendto(sockfd, msg.c_str(), msg.size(), 0,
                       (struct sockaddr *)&clientAddr, addr_len);
            } else {
                std::cout << "(Waiting for client to send something first...)\n";
            }
        }
        close(sockfd);
        exit(0);
    });

    recvThread.join();
    sendThread.join();

    return 0;
}
