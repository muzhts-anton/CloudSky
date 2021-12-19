#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "gtest/gtest.h"
#include "TCPClientSocket.h"
#include "UDPClientSocket.h"
#include "createFilesToSend.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    std::vector<std::string> filesToSend;
    createFilesToSend(&filesToSend);
    std::vector<std::string> filesToReceive;
    int newPort = 8080;
    TCPClient::TCPClientSocket TCPSocket(newPort, "127.0.0.1");
    TCPSocket.activateSocket();
    UDPClient::UDPClientSocket UDPSocket(newPort, "127.0.0.1");
    UDPSocket.activateSocket();
    std::string fileToSendPath = "buttonsCoords.bin";
    std::string fileToReceivePath = "receivedFile.bin";
    for (size_t i = 0; i < filesToSend.size(); i++)
    {
        filesToReceive.push_back(std::to_string(i));
        try {
            TCPSocket.transmitFile(filesToSend.at(i));
            usleep(100000);
            UDPSocket.receiveFile(filesToReceive.at(i));
            compareFiles(filesToSend.at(i), filesToReceive.at(i));
        } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        }
    }
    return RUN_ALL_TESTS();
    return 0;
}