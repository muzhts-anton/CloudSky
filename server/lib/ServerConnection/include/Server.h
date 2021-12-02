#ifndef SERVER_HPP_

#define SERVER_HPP_

#include <fstream>
#include <iostream>

#include "TCPServerSocket.h"
#include "UDPServerSocket.h"

constexpr int serverDefaultPort = 8050;
constexpr const char* serverDefaultIp = "127.0.0.1";

using namespace TCPServer;
using namespace UDPServer;

class Server {
public:
    Server(int port = serverDefaultPort, const char* ip = serverDefaultIp);

    ~Server();

    void start();

    void startNewWorker();

    void getInteraction(std::string filename);

    void sendFile(std::string filename);

private:
    TCPServerSocket* TCPSocket;
    UDPServerSocket* UDPSocket;
    char* hostName;
    int currentWorkerPort;
};

#endif