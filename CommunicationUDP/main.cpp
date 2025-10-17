#include "UDPServer.h" 
#include "test_file.h"   
#include <iostream>

#define PORT 8080

int main() {
    try {
        print();
        UDPServer server(PORT);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}