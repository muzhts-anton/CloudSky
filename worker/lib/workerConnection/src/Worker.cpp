#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <thread>

#include "Worker.h"
#include "constants.h"

#include <unistd.h>

using namespace TCPWorker;
using namespace UDPWorker;

Worker::Worker(int port, const char* ip)
{
    currentWorkerPort = port;
    workerIP = ip;
    TCPSocket = new TCPWorkerSocket(port, ip);
    UDPSocket = new UDPWorkerSocket(port, ip);
}

Worker::Worker(const char* port, const char* ip)
{
    int numberPort = std::stoi(port);
    currentWorkerPort = numberPort;
    workerIP = ip;
    TCPSocket = new TCPWorkerSocket(numberPort, ip);
    UDPSocket = new UDPWorkerSocket(numberPort, ip);
}

Worker::~Worker()
{
    delete TCPSocket;
    delete UDPSocket;
}

void Worker::start()
{
    TCPSocket->activateSocket();
    UDPSocket->activateSocket();
}

void Worker::getInteraction(std::string filename)
{
    try {
        TCPSocket->receiveFile(filename);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        delete TCPSocket;
        TCPSocket = new TCPWorkerSocket(currentWorkerPort, &workerIP[0]);
        TCPSocket->activateSocket();
        receiveClientIP();
    }
}

void Worker::receiveClientIP()
{
    clientIP.clear();
    clientIP = TCPSocket->receiveClientIP();
}

void Worker::sendFile(std::string filename)
{
    try {
        UDPSocket->transmitFile(filename);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Worker::sendData(const char* data, size_t size)
{
    try {
        UDPSocket->transmitData(data, size);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
