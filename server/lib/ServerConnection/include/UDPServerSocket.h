#ifndef UDPSERVERSOCKET_HPP_

#define UDPSERVERSOCKET_HPP_

#include <iostream>

#include <iostream>

#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr int defaultServerUDPPort = 8050;
constexpr const char* defaultServerUDPIp = "127.0.0.1";

namespace UDPServer {
class UDPServerSocket {
public:
    UDPServerSocket(const int port = defaultServerUDPPort, const char* ip = defaultServerUDPIp);

    ~UDPServerSocket();

    void createSocket();

    void createConnection();

    void activateSocket();

    void transmitFile(std::string filename);

private:
    std::fstream file;
    int PORT;
    const char* IP;
    int generalSocketDescriptor;
    struct sockaddr_in address;
    int addressLength;
};
}

#endif