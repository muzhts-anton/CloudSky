#ifndef TCPCLIENTSOCKET_HPP_

#define TCPCLIENTSOCKET_HPP_

#include <iostream>

#include<iostream>
#include<fstream>
#include<stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr int defaultClientPort = 8050;
constexpr const char *defaultClientIp = "127.0.0.1";

namespace TCPClient {
class TCPClientSocket{
public:
    TCPClientSocket(const int port=defaultClientPort, const char *ip=defaultClientIp);

    void createSocket();

    void createConnection();
    
    void activateSocket();

    void transmit_file(std::string filename);
private:
    std::fstream file;
    int PORT;
    const char *IP;
    int generalSocketDescriptor;
    struct sockaddr_in address;
    int addressLength;
};
}

#endif