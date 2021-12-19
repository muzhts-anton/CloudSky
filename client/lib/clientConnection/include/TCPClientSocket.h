#ifndef TCPCLIENTSOCKET_HPP_

#define TCPCLIENTSOCKET_HPP_

#include <iostream>

#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

constexpr int defaultClientPort = 8050;
constexpr const char* defaultClientIp = "127.0.0.1";

namespace TCPClient {
class TCPClientSocket {
public:
    TCPClientSocket(const int port = defaultClientPort, const char* ip = defaultClientIp);

    ~TCPClientSocket();

    void createSocket();

    void createConnection();

    void activateSocket();

    std::string receiveIP();

    void sendIP();

    void changeIP(std::string IP);

    void transmitFile(std::string filename);

private:
    std::fstream file;
    int PORT;
    std::string IP;
    int generalSocketDescriptor;
    struct sockaddr_in address;
    int addressLength;
};
}

#endif