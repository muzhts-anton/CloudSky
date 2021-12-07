#include <iostream>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

int main()
{
    TCPClient::TCPClientSocket TCPSocket1(8080, "10.147.18.164");
    TCPSocket1.activateSocket();
    int newPort = TCPSocket1.receivePortNumber();
    std::cout << "Переключаемся на порт " << newPort << std::endl;
    // TCPSocket.changePort(newPort);
    usleep(1000000);
    TCPClient::TCPClientSocket TCPSocket(newPort, "10.147.18.164");
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(newPort, "10.147.18.164");
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
