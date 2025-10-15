#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <string>
#include <thread>
#include <arpa/inet.h>

class UDPServer {
public:
	// Constructor de khoi tao server voi port cu the
	UDPServer(int port);
	// Destructor de don dep tai nguyen khi server bi huy
	~UDPServer();

	// Ham bat dau chay server (tao ra cac thread)
	void start();
	// Ham de dung server
	void stop();

private:
	void receiveLoop();
	void sendLoop();

	int sockfd;
	int port;
	struct sockaddr_in serverAddr, clientAddr;
	socklen_t addr_len;
	char buffer[1024];

	bool clientConnected;
	bool isRunning;

	std::thread recvThread;
	std::thread sendThread;

};

#endif //UDPSERVER_H
