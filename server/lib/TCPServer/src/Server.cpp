#include <iostream>
#include <stdexcept>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Server.h"
#include "Interactions.h"
#include "SoundComponent.h"
#include "VideoComponent.h"
#include "DataBaseHandler.h"
#include "constants.h"

#include <unistd.h>

using namespace TCPServer;
using namespace UDPServer;

Server::Server(int port, const char *ip) {
    TCPSocket = new TCPServerSocket(port, ip);
    UDPSocket = new UDPServerSocket(port, ip);
}

Server::~Server() {
    delete TCPSocket;
    delete UDPSocket;
}

void Server::start() {
    TCPSocket->activateSocket();
    UDPSocket->activateSocket();
}

void Server::getInteraction() {
    TCPSocket->receiveFile();
}

void Server::sendFile(std::string filename) {
    UDPSocket->transmitFile(filename);
}
