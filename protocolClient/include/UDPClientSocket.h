#ifndef UDPCLIENTSOCKET_HPP_

#define UDPCLIENTSOCKET_HPP_

#include <iostream>

class UDPClientSocket {
    public:

    void getVideo(char *data, size_t size);

    void getAudio(char *data, size_t size);

    void setPort(uint16_t port);

    uint16_t getPort();

    private:

    uint16_t UDPClientPort;
};

#endif