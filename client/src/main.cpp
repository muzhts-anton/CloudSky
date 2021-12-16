#include <iostream>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

constexpr int defaultPort = 8080;
constexpr const char *defaultIp = "10.147.18.164";
constexpr int initSleepAmount = 1000000;
constexpr double defaultFPS = 0.5;
constexpr double iterationSleepAmount = 1000.0;

int main()
{
    TCPClient::TCPClientSocket TCPSocket1(defaultPort, defaultIp);
    TCPSocket1.activateSocket();
    int newPort = TCPSocket1.receivePortNumber();
    std::cout << "Переключаемся на порт " << newPort << std::endl;
    usleep(1000000);
    TCPClient::TCPClientSocket TCPSocket(newPort, defaultIp);
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(newPort, defaultIp);
    UDPSocket.activateSocket();
    double fps = defaultFPS;
    std::string fileToSendPath = "buttonsCoords.bin";
    std::string fileToReceivePath = "receivedFile.bin";
    while (true) {
        try {
            TCPSocket.transmitFile(fileToSendPath);
            UDPSocket.receiveFile(fileToReceivePath);
        } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        }
        usleep(iterationSleepAmount / fps);
    }
    return 0;
}
