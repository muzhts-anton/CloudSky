#include "UDPClientSocket.h"
#include "constants.h"

#include <iostream>
#include <fstream>

constexpr int debug = 1;

using namespace UDPClient;

UDPClientSocket::UDPClientSocket(int port, const char *ip) {
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

UDPClientSocket& UDPClientSocket::operator=(UDPClientSocket& that) {
    PORT = that.PORT;
    IP = that.IP;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
    return *this;
}

UDPClientSocket::~UDPClientSocket() {
    if (file.is_open())
        file.close();
    close(generalSocketDescriptor);
}

void UDPClientSocket::activateSocket() {
    createSocket();
    bindSocket();
}

void UDPClientSocket::createSocket(){
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) { 
        if (debug)
            perror("[ERROR] : UPD Socket failed.\n");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout<<"[LOG] : UPD Socket Created Successfully.\n";
}

void UDPClientSocket::bindSocket(){
    if (bind(generalSocketDescriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        if (debug)  
            perror("[ERROR] : UPD Bind failed");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout<<"[LOG] : UPD Bind Successful.\n";
}

void UDPClientSocket::receiveFile(std::string fileToReceivePath){
    file.open(fileToReceivePath, std::ios::out | std::ios::trunc | std::ios::binary);
    if(file.is_open()) {
        if (debug)
            std::cout<<"[LOG] : UPD File Created.\n";
    }
    else {
        if (debug)
            std::cout<<"[ERROR] : UPD File creation failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
    char buffer[1024] = {};
    unsigned len = 0;
    int valread = recvfrom(generalSocketDescriptor, buffer, 1024, MSG_DONTWAIT, \
    (struct sockaddr *) &address, &len);
    //int valread = read(newSocketDescriptor, buffer, 1024);
    if (debug) {
        std::cout<<"[LOG] : UPD Data received "<< valread <<" bytes\n";
        std::cout<<"[LOG] : UPD Saving data to file.\n";
    }
    for (int i = 0; i < valread; i++)
        file.write(buffer + i, 1);
    file.close();
    if (debug)  
        std::cout<<"[LOG] : UPD File Saved.\n";
}
