#include <iostream>
#include <vector>
#include <string>

#include "TCPClientSocket.h"
#include "UDPClientSocket.h"
#include "createFilesToSend.h"

int main()
{
    std::vector<std::string> filesToSend;
    createFilesToSend(&filesToSend);
    int newPort = 8080;
    TCPClient::TCPClientSocket TCPSocket(newPort, "127.0.0.1");
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(newPort, "127.0.0.1");
    UDPSocket.activateSocket();
    std::string fileToSendPath = "buttonsCoords.bin";
    std::string fileToReceivePath = "receivedFile.bin";
    for (int i = 0; i < filesToSend.size(); i++)
    {
        try {
            TCPSocket.transmitFile(filesToSend.at(i));
        } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        }
    }
    //UDPSocket.receiveFile(fileToReceivePath);
    return 0;
}