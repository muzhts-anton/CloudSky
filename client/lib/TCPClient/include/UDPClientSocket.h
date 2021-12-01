#ifndef UDPCLIENTSOCKET_HPP_

#define UDPCLIENTSOCKET_HPP_

#include <iostream>

#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr int defaultServerPort = 8050;
constexpr const char *defaultServerIp = "127.0.0.1";

namespace UDPClient {
class UDPClientSocket {
public:

    UDPClientSocket(int port=defaultServerPort, const char *ip=defaultServerIp);

    UDPClientSocket& operator=(UDPClientSocket& that);

    ~UDPClientSocket();

    void activateSocket();

    void bindSocket();

    void setListenSet();

    void acceptConnection();

    void createSocket();

    void receiveFile(std::string fileToReceivePath);

private:

    std::fstream file;
    int PORT;
    int generalSocketDescriptor;
    int newSocketDescriptor;
    struct sockaddr_in address;
    struct sockaddr_in clientAddress;
    int addressLength;
    const char *IP;
};
}

#endif