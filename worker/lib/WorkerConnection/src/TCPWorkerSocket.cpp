#include "TCPWorkerSocket.h"

#include <fstream>
#include <iostream>

constexpr int debug = 1;

using namespace TCPWorker;

TCPWorkerSocket::TCPWorkerSocket(int port, const char* ip)
{
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

TCPWorkerSocket& TCPWorkerSocket::operator=(TCPWorkerSocket& that)
{
    PORT = that.PORT;
    IP = that.IP;
    address.sin_family = AF_INET;
    //address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
    return *this;
}

TCPWorkerSocket::~TCPWorkerSocket()
{
    if (file.is_open())
        file.close();
    char buff[10] = { 0 };
    while (recv(newSocketDescriptor, buff, 10, 0) > 0) { }
    close(newSocketDescriptor);
    close(generalSocketDescriptor);
}

void TCPWorkerSocket::activateSocket()
{
    try {
            createSocket();
            if (inet_pton(AF_INET, IP, &address.sin_addr) <= 0) {
            if (debug)
                std::cout << "[ERROR] : TCP Invalid address\n";
            } else {
                bindSocket();
                setListenSet();
                acceptConnection();
            }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void TCPWorkerSocket::createSocket()
{
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        if (debug)
            std::cerr << "[ERROR] : TCP Socket failed." << std::endl;
        throw std::invalid_argument("[ERROR] : TCP Socket failed.");
    }
    if (debug)
        std::cout << "[LOG] : TCP Socket Created Successfully.\n";
}

void TCPWorkerSocket::bindSocket()
{
    if (bind(generalSocketDescriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
        if (debug)
            std::cerr << "[ERROR] : TCP Bind failed." << std::endl;
        throw std::invalid_argument("[ERROR] : TCP Bind failed.");
    }
    if (debug)
        std::cout << "[LOG] : TCP Bind Successful.\n";
}

void TCPWorkerSocket::setListenSet()
{
    if (listen(generalSocketDescriptor, 3) < 0) {
        if (debug)
            std::cerr << "[ERROR] : TCP Listen" << std::endl;
        throw std::invalid_argument("[ERROR] : TCP Listen.");
    }
    if (debug)
        std::cout << "[LOG] : TCP Socket in Listen State (Max Connection Queue: 3)\n";
}

void TCPWorkerSocket::acceptConnection()
{
    if ((newSocketDescriptor = accept(generalSocketDescriptor, (struct sockaddr*)&address, (socklen_t*)&addressLength)) < 0) {
        if (debug)
            std::cerr << "[ERROR] : TCP Accept." << std::endl;
        throw std::invalid_argument("[ERROR] : TCP Accept.");
    }
    if (debug)
        std::cout << "[LOG] : TCP Connected to Server.\n";
}

void TCPWorkerSocket::sendNewWorkerPort(int newPort)
{
    char buffer[20] = { 0 };
    int length = std::snprintf(buffer, 20, "%d", newPort);
    send(newSocketDescriptor, buffer, length, 0);
}

void TCPWorkerSocket::receiveFile(std::string filename)
{
    file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    if (file.is_open()) {
        if (debug)
            std::cout << "[LOG] : TCP File Created.\n";
    } else {
        if (debug)
            std::cerr << "[ERROR] : TCP File creation failed." << std::endl;
        throw std::invalid_argument("[ERROR] : TCP File creation failed.");
    }
    char buffer[1024] = {};
    int valread = read(newSocketDescriptor, buffer, 1024);
    if (debug) {
        std::cout << "[LOG] : TCP Data received " << valread << " bytes\n";
        std::cout << "[LOG] : TCP Saving data to file.\n";
    }
    if (valread == 0) {
        std::cerr << "[LOG] : TCP Client is not connected anymore. Maybe I should exit...\n";
    }
    for (int i = 0; i < valread; i++)
        file.write(buffer + i, 1);
    file.close();
    if (debug)
        std::cout << "[LOG] : TCP File Saved.\n";
}
