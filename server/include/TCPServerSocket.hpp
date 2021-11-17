#ifndef TCPSERVERSOCKET_HPP_

#define TPCSERVERSOCKET_HPP_

#include <iostream>

class TCPServerSocket {
    public:

    void getInteraction(FILE *src);
    void getHostName(std::string *hostName);

    private:

    uint16_t TCPServerPort;
}

#endif