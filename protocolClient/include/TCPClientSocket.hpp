#ifndef TCPCLIENTSOCKET_HPP_

#define TCPCLIENTSOCKET_HPP_

#include <iostream>

class TCPClientSocket {
    public:

    void sendInteraction(FILE *src);

    void start();

    private:

    uint16_t TCPClientPort;
};

#endif