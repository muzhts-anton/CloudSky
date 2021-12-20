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

constexpr int defaultWorkerPort = 8080;
constexpr const char* defaultWorkerIp = "10.147.18.218";
constexpr const char* defaultServerIp = "10.147.18.164";
constexpr const char* workerIP = "10.147.18.204";
constexpr const char *workerFreedom = "FREE";
constexpr int workerIPLength = 14;

namespace TCPWorker {
class TCPWorkerSocket {
public:
    TCPWorkerSocket(int port = defaultWorkerPort, const char* ip = defaultWorkerIp);

    TCPWorkerSocket& operator=(TCPWorkerSocket& that);

    ~TCPWorkerSocket();

    void activateSocket();

    void activateSendSocket();

    void bindSocket();

    void setListenSet();

    void acceptConnection();

    void createSocket();

    void createConnection();

    std::string receiveClientIP();

    void receiveFile(std::string filename);

    void sendSignal();

private:

    void sendWorkerIP();

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