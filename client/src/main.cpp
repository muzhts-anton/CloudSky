#include <iostream>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

int main()
{
    TCPClient::TCPClientSocket TCPSocket(8050, "127.0.0.1");
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(8051, "127.0.0.2");
    UDPSocket.activateSocket();
    int fps = 1;
    std::string fileToSendPath = "buttonsCoords.bin";
    std::string fileToReceivePath = "receivedFile.bin";
    while (true)
    {
        TCPSocket.transmitFile(fileToSendPath);
        usleep(1000.0 / fps);
    }
    return 0;
}
