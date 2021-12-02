#ifndef TCPSERVERSOCKET_H_

#define TPCSERVERSOCKET_H_

#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr int defaultServerPort = 8050;
constexpr const char* defaultServerIp = "127.0.0.1";

namespace TCPServer {
class TCPServerSocket {
public:
    TCPServerSocket(int port = defaultServerPort, const char* ip = defaultServerIp);

    TCPServerSocket& operator=(TCPServerSocket& that);

    ~TCPServerSocket();

    void activateSocket();

    void bindSocket();

    void setListenSet();

    void acceptConnection();

    void createSocket();

    void receiveFile(std::string filename);

private:
    std::fstream file;
    int PORT;
    int generalSocketDescriptor;
    int newSocketDescriptor;
    struct sockaddr_in address;
    int addressLength;
    const char* IP;
};
}

#endif