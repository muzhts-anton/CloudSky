#include "TCPClientSocket.h"
#include "constants.h"

constexpr bool debug = true;

TCPClient::TCPClientSocket::TCPClientSocket(const int port, const char *ip){  
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_port = htons( PORT );
    addressLength = sizeof(address);
}

void TCPClient::TCPClientSocket::activateSocket() {
    createSocket();
    if(inet_pton(AF_INET, IP, &address.sin_addr)<=0) { 
        if (debug)
            std::cout<<"[ERROR] : TCP Invalid address\n";
    }
    else
        createConnection();
}

void TCPClient::TCPClientSocket::createSocket(){
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) { 
        if (debug)
            perror("[ERROR] : TCP Socket failed");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout<<"[LOG] : TCP Socket Created Successfully.\n";
}

void TCPClient::TCPClientSocket::createConnection(){
    if (connect(generalSocketDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        if (debug)
            perror("[ERROR] : TCP connection attempt failed.\n");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout<<"[LOG] : TCP Connection Successfull.\n";
}

void TCPClient::TCPClientSocket::transmitFile(std::string filename){
    file.open(filename, std::ios::in | std::ios::binary);
    if(file.is_open()) {
        if (debug)
            std::cout<<"[LOG] : TCP File is ready to Transmit.\n";
    }
    else {
        if (debug)
            std::cout<<"[ERROR] : TCP File loading failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
    //std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    ///std::cout<<"[LOG] : Transmission Data Size "<<contents.length()<<" Bytes.\n";
    char buffer[1024] = {};
    int length = 0;
    while (!file.eof()) {
        file.get(buffer[length]);
        length++;
    }
    if (debug)
        std::cout<<"[LOG] : TCP Sending...\n";

    int bytes_sent = send(generalSocketDescriptor , buffer , length - 1, 0 );
    file.close();
    if (debug) {
        std::cout<<"[LOG] : TCP Transmitted Data Size "<< bytes_sent <<" Bytes.\n";
        std::cout<<"[LOG] : TCP File Transfer Complete.\n";
    }
}