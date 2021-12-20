#ifndef WORKER_H_

#define WORKER_H_

#include <fstream>
#include <iostream>

#include "TCPWorkerSocket.h"
#include "UDPWorkerSocket.h"

constexpr int workerDefaultPort = 8050;
constexpr const char* workerDefaultPortStr = "8050";
constexpr const char* workerDefaultIp = "127.0.0.1";

using namespace TCPWorker;
using namespace UDPWorker;

class Worker {
public:
    Worker(int port = workerDefaultPort, const char* ip = workerDefaultIp);

    Worker(const char *port = workerDefaultPortStr, const char* ip = workerDefaultIp);

    ~Worker();

    void start();

    void receiveClientIP();

    void getInteraction(std::string filename);

    void sendFile(std::string filename);

    void sendData(const char* data, size_t size);

    std::string getClientIP();

private:
    TCPWorkerSocket* TCPSocket;
    UDPWorkerSocket* UDPSocket;
    int currentWorkerPort;
    std::string workerIP;
    std::string clientIP;
};

#endif