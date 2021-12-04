#include <iostream>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

int main()
{
    TCPClient::TCPClientSocket TCPSocket(8050, "127.0.0.1");
    TCPSocket.activateSocket();
    // int newPort = TCPSocket.receivePortNumber();
    // std::cout << "Переключаемся на порт " << newPort << std::endl;
    UDPClient::UDPClientSocket UDPSocket(8050, "127.0.0.1");
    UDPSocket.activateSocket();
    double fps = 0.5;
    std::string fileToSendPath = "buttonsCoords.bin";
    std::string fileToReceivePath = "receivedFile.bin";
    while (true) {
        try {
            TCPSocket.transmitFile(fileToSendPath);
            UDPSocket.receiveFile(fileToReceivePath);
        } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        }
        usleep(1000.0 / fps);
    }
    return 0;
}
