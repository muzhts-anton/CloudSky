#include <iostream>
#include <stdexcept>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Server.h"
//#include "TCPServerSocket.h"
#include "UDPServerSocket.h"
#include "Interactions.h"
#include "SoundComponent.h"
#include "VideoComponent.h"
#include "DataBaseHandler.h"
#include "constants.h"

#include <unistd.h>

Server::Server(int port, const char *ip) {
    serverSocket = new TCPServerSocket(port, ip);
}

Server::~Server() {
    delete serverSocket;
}

void Server::start() {
    serverSocket->activateSocket();
}

void Server::getInteraction() {
    serverSocket->receiveFile();
}

int main() {
    Server server;
    server.start();
    int fps = 40;
    while (true)
    {
        server.getInteraction();
        usleep(1000.0 / fps);
    }
    return 0;
}