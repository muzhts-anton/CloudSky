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
    TCPClient::TCPClientSocket TCPSocket(defaultPort, defaultIp);
    TCPSocket.activateSocket();
    std::string newIP = TCPSocket.receiveIP();
    std::cout << "Переключаемся на IP " << newIP << std::endl;
    usleep(1000000);
    TCPSocket.changeIP(newIP);
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(defaultPort, &newIP[0]);
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
