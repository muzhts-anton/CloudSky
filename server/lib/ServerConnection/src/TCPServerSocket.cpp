#include "TCPServerSocket.h"

#include <fstream>
#include <iostream>

constexpr int debug = 1;

using namespace TCPServer;

TCPServerSocket::TCPServerSocket(int port, const char* ip)
{
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

TCPServerSocket& TCPServerSocket::operator=(TCPServerSocket& that)
{
    PORT = that.PORT;
    IP = that.IP;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
    return *this;
}

TCPServerSocket::~TCPServerSocket()
{
    if (file.is_open())
        file.close();
    char buff[10] = { 0 };
    while (recv(newSocketDescriptor, buff, 10, 0) > 0) { }
    close(newSocketDescriptor);
    close(generalSocketDescriptor);
}

void TCPServerSocket::activateSocket()
{
    createSocket();
    bindSocket();
    setListenSet();
    acceptConnection();
}

void TCPServerSocket::createSocket()
{
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        if (debug)
            perror("[ERROR] : TCP Socket failed.\n");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout << "[LOG] : TCP Socket Created Successfully.\n";
}

void TCPServerSocket::bindSocket()
{
    if (bind(generalSocketDescriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
        if (debug)
            perror("[ERROR] : TCP Bind failed");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout << "[LOG] : TCP Bind Successful.\n";
}

void TCPServerSocket::setListenSet()
{
    if (listen(generalSocketDescriptor, 3) < 0) {
        if (debug)
            perror("[ERROR] : TCP Listen");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout << "[LOG] : TCP Socket in Listen State (Max Connection Queue: 3)\n";
}

void TCPServerSocket::acceptConnection()
{
    if ((newSocketDescriptor = accept(generalSocketDescriptor, (struct sockaddr*)&address, (socklen_t*)&addressLength)) < 0) {
        if (debug)
            perror("[ERROR] : TCP Accept");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout << "[LOG] : TCP Connected to Server.\n";
}

void TCPServerSocket::sendNewWorkerPort(int newPort)
{
    char buffer[20] = { 0 };
    int length = std::snprintf(buffer, 20, "%d", newPort);
    send(newSocketDescriptor, buffer, length, 0);
}

void TCPServerSocket::receiveFile(std::string filename)
{
    file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (file.is_open()) {
        if (debug)
            std::cout << "[LOG] : TCP File Created.\n";
    } else {
        if (debug)
            std::cout << "[ERROR] : TCP File creation failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
    char buffer[1024] = {};
    int valread = read(newSocketDescriptor, buffer, 1024);
    if (debug) {
        std::cout << "[LOG] : TCP Data received " << valread << " bytes\n";
        std::cout << "[LOG] : TCP Saving data to file.\n";
    }
    if (valread == 0) {
        std::cout << "[LOG] : TCP Client is not connected anymore, exiting...\n";
        exit(0);
    }
    for (int i = 0; i < valread; i++)
        file.write(buffer + i, 1);
    file.close();
    if (debug)
        std::cout << "[LOG] : TCP File Saved.\n";
}
