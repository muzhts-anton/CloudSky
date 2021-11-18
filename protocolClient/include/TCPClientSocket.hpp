#ifndef TCPCLIENTSOCKET_HPP_

#define TCPCLIENTSOCKET_HPP_

#include <iostream>

class TCPClientSocket {
    public:

    void sendInteraction(FILE *src);

    void start();

    void stop();

    void setPort(uint16_t port);

    uint16_t getPort();

    private:

    uint16_t TCPClientPort;
};

#endif