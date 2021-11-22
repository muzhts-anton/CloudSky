#ifndef SERVER_HPP_

#define SERVER_HPP_

#include <iostream>
#include <fstream>

#include "TCPServerSocket.h"

constexpr int serverDefaultPort = 8050;
constexpr const char *serverDefaultIp = "127.0.0.1";

// class Server {
//     public:

//     uint16_t getPort()  const;
//     uint16_t setPort(const uint16_t port);
//     int getStatus();
//     void stop();
//     void start();
//     void restart();
//     void getInteraction();
//     void sendGameScreen(char *data, size_t size);
//     void setHostName();
//     void sendGameAudio(char *data, size_t size);

//     private:

//     uint16_t TCPServerPort;
//     uint16_t UDPServerPort;
//     std::string hostName;
//     bool isRunning;

// };

class Server {
public:
    Server(int port=serverDefaultPort, const char *ip=serverDefaultIp);

    ~Server();

    void start();

    void getInteraction();

private:
    TCPServerSocket *serverSocket;
    char *hostName;
};

#endif