#ifndef UDPSERVERSOCKET_HPP_

#define UPDSERVERSOCKET_HPP_

#include <iostream>

class  UDPServerSocket {
    public:

    void sendVideo(char *data, size_t  size) ;
    void sendAudio(char *data, size_t  size);
    
    private:

    uint16_t UDPServerPort;
};

#endif