#ifndef TCPWORKERSOCKET_H_

#define TPCWORKERSOCKET_H_

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

namespace TCPWorker {
class TCPWorkerSocket {
public:
    TCPWorkerSocket(int port = defaultServerPort, const char* ip = defaultServerIp);

    TCPWorkerSocket& operator=(TCPWorkerSocket& that);

    ~TCPWorkerSocket();

    void activateSocket();

    void bindSocket();

    void setListenSet();

    void acceptConnection();

    void createSocket();

    void sendNewWorkerPort(int newPort);

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