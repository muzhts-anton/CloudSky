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
    int i = 0;
    while (i < 1)//for (int i = 0; i < 1000; i++)
    {
        server.getInteraction();
        i++;
        //usleep(100000);
    }
    return 0;
}