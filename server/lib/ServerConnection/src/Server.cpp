#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>

#include "DataBaseHandler.h"
#include "Interactions.h"
#include "Server.h"
#include "SoundComponent.h"
#include "VideoComponent.h"
#include "constants.h"

#include <unistd.h>

using namespace TCPServer;
using namespace UDPServer;

Server::Server(int port, const char* ip)
{
    TCPSocket = new TCPServerSocket(port, ip);
    UDPSocket = new UDPServerSocket(port, ip);
    currentWorkerPort = port + 1;
}

Server::~Server()
{
    delete TCPSocket;
    delete UDPSocket;
}

void Server::start()
{
    TCPSocket->activateSocket();
    UDPSocket->activateSocket();
}

void Server::startNewWorker()
{
    std::cout << "Начинаем передавать данные о новом worker-e" << std::endl;
    TCPSocket->sendNewWorkerPort(currentWorkerPort);
    std::cout << "Новый worker на порту " << currentWorkerPort++ << std::endl;
}

void Server::getInteraction(std::string filename)
{
    try {
        TCPSocket->receiveFile(filename);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Server::sendFile(std::string filename)
{
    try {
        UDPSocket->transmitFile(filename);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
