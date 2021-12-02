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

void Server::getInteraction(std::string filename)
{
    TCPSocket->receiveFile(filename);
}

void Server::sendFile(std::string filename)
{
    UDPSocket->transmitFile(filename);
}
