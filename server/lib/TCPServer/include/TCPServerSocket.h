#ifndef TCPSERVERSOCKET_H_

#define TPCSERVERSOCKET_H_

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

namespace TCPServer {
class TCPServerSocket {
public:

    TCPServerSocket(int port=defaultServerPort, const char *ip=defaultServerIp);

    TCPServerSocket& operator=(TCPServerSocket& that);

    ~TCPServerSocket();

    void activateSocket();

    void bindSocket();

    void setListenSet();

    void acceptConnection();

    void createSocket();

    void receiveFile();

private:

    std::fstream file;
    int PORT;
    int generalSocketDescriptor;
    int newSocketDescriptor;
    struct sockaddr_in address;
    int addressLength;
    const char *IP;
};
}

#endif