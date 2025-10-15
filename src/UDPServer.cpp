#include "UDPServer.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

//Constructor
UDPServer::UDPServer(int port)
    : port(port), sockfd(-1), clientConnected(false), isRunning(false) {
	// Tao socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		throw std::runtime_error("Socket creation failed");
	}
	// Thiet lap dia chi server
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(this->port);

	// Bind socket vao dia chi server
	if (bind(sockfd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        close(sockfd);
        throw std::runtime_error("Bind failed");
    }

    addr_len = sizeof(clientAddr);
    std::cout << "UDP Server is ready on port " << this->port << "...\n";
}

// Destructor
UDPServer::~UDPServer() {
	stop();
	if (sockfd >= 0) {
		close(sockfd);
	}
}

//Bat dau chay server
void UDPServer::start() {
	isRunning = true;
	// Tao va chay 2 thread, tro de cac ham con
	recvThread = std::thread(&UDPServer::receiveLoop, this);
	sendThread = std::thread(&UDPServer::sendLoop, this);

	// Cho den khi cac thread ket thuc
	sendThread.join();
	recvThread.join();
}

void UDPServer::stop() {
	isRunning = false;
}


//Thread  nhan du lieu
void UDPServer::receiveLoop() {
	while (isRunning) {
	memset(buffer, 0, 1024);
        ssize_t len = recvfrom(sockfd, buffer, 1023, 0, (struct sockaddr *)&clientAddr, &addr_len);

	if (len > 0) {
		buffer[len] = '\0';
		if (!clientConnected) {
        		clientConnected = true;
                	std::cout << "\nClient connected!\n";
		}
            std::cout << "\nClient: " << buffer << std::endl;
            std::cout << "Server> " << std::flush;
        }
    }

}

//Thread gui du lieu
void UDPServer::sendLoop() {
    std::string msg;
    while (isRunning) {
        std::cout << "Server> ";
        std::getline(std::cin, msg);
        if (msg == "exit") {
            stop(); // Dừng các luồng khác
            break;
        }

        if (clientConnected) {
            sendto(sockfd, msg.c_str(), msg.size(), 0, (const struct sockaddr *)&clientAddr, addr_len);
        } else {
            std::cout << "(Waiting for a client to connect...)\n";
        }
    }
}
