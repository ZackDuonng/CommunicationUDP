#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t addr_len = sizeof(servaddr);
    char buffer[BUFFER_SIZE];

    // 1️⃣ Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 2️⃣ Setup server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.137.5", &servaddr.sin_addr); // 🔁 Pi IP

    std::cout << "✅ UDP Client started (type 'exit' to quit)\n";

    // 3️⃣ Thread for receiving messages
    std::thread recvThread([&]() {
        while (true) {
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t len = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0, nullptr, nullptr);
            if (len < 0) {
                perror("recvfrom error");
                break;
            }

            buffer[len] = '\0';
            std::cout << "\n📩 Server: " << buffer << std::endl;
            std::cout << "Client> " << std::flush;
        }
    });

    // 4️⃣ Thread for sending messages
    std::thread sendThread([&]() {
        std::string msg;
        while (true) {
            std::cout << "Client> ";
            std::getline(std::cin, msg);
            if (msg == "exit") break;

            sendto(sockfd, msg.c_str(), msg.size(), MSG_CONFIRM,
                   (const struct sockaddr *)&servaddr, addr_len);
        }
        close(sockfd);
        exit(0);
    });

    recvThread.join();
    sendThread.join();

    return 0;
}
