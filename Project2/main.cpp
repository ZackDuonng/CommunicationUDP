#include "CommunicationUDP/include/UDPServer.h" 
#include "CommunicationUDP/include/test_file.h"   
#include <iostream>

#define PORT 8080

int main() {
    std::cout<<"Chuong trinh dang chay ne !!!"<<std::endl;
    int *ptr  = new int[10];
    std::cout << "Address of allocated memory: " << ptr[11] << std::endl;
    return 0;
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