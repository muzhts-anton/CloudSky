#include "UDPWorkerSocket.h"

#include "constants.h"

constexpr bool debug = true;

UDPWorker::UDPWorkerSocket::UDPWorkerSocket(const int port, const char* ip)
{
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

UDPWorker::UDPWorkerSocket::~UDPWorkerSocket()
{
    close(generalSocketDescriptor);
}

void UDPWorker::UDPWorkerSocket::activateSocket()
{
    try {
        createSocket();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void UDPWorker::UDPWorkerSocket::createSocket()
{
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == 0) {
        if (debug)
            std::cerr << "[ERROR] : UPD Socket failed." << std::endl;
        throw std::invalid_argument("[ERROR] : UPD Socket failed.");
    }
    if (debug)
        std::cout << "[LOG] : UPD Socket Created Successfully." << std::endl;
}

void UDPWorker::UDPWorkerSocket::transmitFile(std::string filename)
{
    file.open(filename, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        if (debug)
            std::cout << "[LOG] : UPD File is ready to Transmit." << std::endl;
    } else {
        if (debug)
            std::cerr << "[ERROR] : UPD File loading failed. Maybe I should exit..." << std::endl;
        throw std::invalid_argument("[ERROR] : UPD File loading failed. Maybe I should exit...");
    }
    char buffer[1024] = {};
    int length = 0;
    while (!file.eof()) {
        file.get(buffer[length]);
        length++;
    }
    if (debug)
        std::cout << "[LOG] : UPD Sending...\n";

    int bytesSent = sendto(generalSocketDescriptor, buffer, length - 1, MSG_DONTWAIT,
        (struct sockaddr*)&address, sizeof(address));

    file.close();
    if (debug) {
        std::cout << "[LOG] : UPD Transmitted Data Size " << bytesSent << " Bytes.\n";
        std::cout << "[LOG] : UPD File Transfer Complete.\n";
    }
}

void UDPWorker::UDPWorkerSocket::transmitData(const char* data, size_t size)
{
    if (debug)
        std::cout << "[LOG] : UDP Sending...\n";

    int bytesSent = sendto(generalSocketDescriptor, data, size, MSG_DONTWAIT,
        (struct sockaddr*)&address, sizeof(address));
        
    if (debug) {
        std::cout << "[LOG] : UDP Transmitted Data Size " << bytesSent << " Bytes.\n";
        std::cout << "[LOG] : UDP Data Transfer Complete.\n";
    }
}