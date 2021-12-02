#include "UDPServerSocket.h"

#include "constants.h"

constexpr bool debug = true;

UDPServer::UDPServerSocket::UDPServerSocket(const int port, const char* ip)
{
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

UDPServer::UDPServerSocket::~UDPServerSocket()
{
    close(generalSocketDescriptor);
}

void UDPServer::UDPServerSocket::activateSocket()
{
    createSocket();
}

void UDPServer::UDPServerSocket::createSocket()
{
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == 0) {
        if (debug)
            perror("[ERROR] : UPD Socket failed");
        exit(EXIT_FAILURE);
    }
    if (debug)
        std::cout << "[LOG] : UPD Socket Created Successfully.\n";
}

void UDPServer::UDPServerSocket::transmitFile(std::string filename)
{
    file.open(filename, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        if (debug)
            std::cout << "[LOG] : UPD File is ready to Transmit.\n";
    } else {
        if (debug)
            std::cout << "[ERROR] : UPD File loading failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
    char buffer[1024] = {};
    int length = 0;
    while (!file.eof()) {
        file.get(buffer[length]);
        length++;
    }
    if (debug)
        std::cout << "[LOG] : UPD Sending...\n";

    int bytesSent = sendto(generalSocketDescriptor, buffer, length, MSG_DONTWAIT,
        (struct sockaddr*)&address, sizeof(address));

    file.close();
    if (debug) {
        std::cout << "[LOG] : UPD Transmitted Data Size " << bytesSent << " Bytes.\n";
        std::cout << "[LOG] : UPD File Transfer Complete.\n";
    }
}