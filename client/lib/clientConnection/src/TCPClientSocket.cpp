#include "TCPClientSocket.h"
#include "constants.h"

constexpr bool debug = true;
// constexpr const char *clientIP = "10.147.18.164";
constexpr const char *clientIP = "127.0.0.1";
constexpr int clientIPLength = 9;

TCPClient::TCPClientSocket::TCPClientSocket(const int port, const char* ip)
{
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

TCPClient::TCPClientSocket::~TCPClientSocket()
{
    if (file.is_open())
        file.close();
    close(generalSocketDescriptor);
}

void TCPClient::TCPClientSocket::activateSocket()
{   
    try {
        createSocket();
        if (inet_pton(AF_INET, &IP[0], &address.sin_addr) <= 0) {
            if (debug)
                std::cout << "[ERROR] : TCP Invalid address\n";
        } else
            createConnection();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void TCPClient::TCPClientSocket::createSocket()
{
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0) {
        if (debug)
            std::cout << "[ERROR] : TCP Socket failed"  << std::endl;
        throw std::invalid_argument("[ERROR] : TCP Socket failed");
    }
    if (debug)
        std::cout << "[LOG] : TCP Socket Created Successfully.\n";
}

void TCPClient::TCPClientSocket::createConnection()
{
    if (connect(generalSocketDescriptor, (struct sockaddr*)&address, sizeof(address)) < 0) {
        if (debug)
            perror("[ERROR] : TCP connection attempt failed.\n");
        throw std::invalid_argument("[ERROR] : TCP connection attempt failed.");
    }
    if (debug)
        std::cout << "[LOG] : TCP Connection Successfull.\n";
}

std::string TCPClient::TCPClientSocket::receiveIP()
{
    char buffer[1024] = {};
    send(generalSocketDescriptor, clientIP, clientIPLength, 0);

    std::string IPString;
    int valread = read(generalSocketDescriptor, buffer, 1024);
    if (debug) {
        std::cout << "[LOG] : TCP Data received " << valread << " bytes\n";
    }
    if (valread > 0 && valread < 14) {
        for (int i = 0; i < valread; i++)
            IPString.push_back(buffer[i]);
    }
    std::cout << IPString << std::endl;
    return IPString;
}

void TCPClient::TCPClientSocket::sendIP()
{
    int bytes_sent = send(generalSocketDescriptor, clientIP, clientIPLength, 0);
    if (debug) {
        std::cout << "[LOG] : TCP Transmitted Data Size " << bytes_sent << " Bytes.\n";
        std::cout << "[LOG] : TCP File Transfer Complete.\n";
    }
}

void TCPClient::TCPClientSocket::changeIP(std::string newIP)
{
    IP = newIP;
    PORT = 8081;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
    try {
        createConnection();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

void TCPClient::TCPClientSocket::transmitFile(std::string filename)
{
    file.open(filename, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        if (debug)
            std::cout << "[LOG] : TCP File is ready to Transmit." << std::endl;
    } else {
        if (debug)
            std::cout << "[ERROR] : TCP File loading failed. Maybe I should exit..." << std::endl;
        throw std::invalid_argument("[ERROR] : TCP File loading failed. Maybe I should exit...");
    }
    char buffer[1024] = {};
    int length = 0;
    while (!file.eof()) {
        file.get(buffer[length]);
        length++;
    }
    if (debug)
        std::cout << "[LOG] : TCP Sending...\n";

    int bytes_sent = send(generalSocketDescriptor, buffer, length - 1, 0);
    file.close();
    if (debug) {
        std::cout << "[LOG] : TCP Transmitted Data Size " << bytes_sent << " Bytes.\n";
        std::cout << "[LOG] : TCP File Transfer Complete.\n";
    }
}