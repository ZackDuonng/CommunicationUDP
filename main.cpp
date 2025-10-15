#include "include/UDPServer.h"
#include <iostream>

#define PORT 8080

int main() {
    try {

        UDPServer server(PORT);
        server.start();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
