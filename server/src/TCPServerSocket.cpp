#include "TCPServerSocket.h"
// #include "../../client/include/keyboard_mouse_message.pb.h"
// #include "../../client/include/message_operations.h"

#include <iostream>
#include <fstream>

TCPServerSocket::TCPServerSocket(int port, const char *ip) {
    PORT = port;
    IP = ip;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
}

TCPServerSocket& TCPServerSocket::operator=(TCPServerSocket& that) {
    PORT = that.PORT;
    IP = that.IP;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);
    addressLength = sizeof(address);
    return *this;
}

TCPServerSocket::~TCPServerSocket() {
    if (file.is_open())
        file.close();
    close(generalSocketDescriptor);
}

void TCPServerSocket::activateSocket() {
    createSocket();
    bindSocket();
    setListenSet();
    acceptConnection();
}

void TCPServerSocket::createSocket(){
    if ((generalSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("[ERROR] : Socket failed.\n");
        exit(EXIT_FAILURE);
    }
    std::cout<<"[LOG] : Socket Created Successfully.\n";
}

void TCPServerSocket::bindSocket(){
    if (bind(generalSocketDescriptor, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("[ERROR] : Bind failed");
        exit(EXIT_FAILURE);
    }
    std::cout<<"[LOG] : Bind Successful.\n";
}

void TCPServerSocket::setListenSet(){
    if (listen(generalSocketDescriptor, 3) < 0) {
        perror("[ERROR] : Listen");
        exit(EXIT_FAILURE);
    }
    std::cout<<"[LOG] : Socket in Listen State (Max Connection Queue: 3)\n";
}

void TCPServerSocket::acceptConnection(){
    if ((newSocketDescriptor = accept(generalSocketDescriptor, (struct sockaddr *)&address, (socklen_t*)&addressLength))<0) { 
        perror("[ERROR] : Accept");
        exit(EXIT_FAILURE);
    }
    std::cout<<"[LOG] : Connected to Server.\n";
}

void TCPServerSocket::receiveFile(){
    file.open("../data/received.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    if(file.is_open()){
        std::cout<<"[LOG] : File Created.\n";
    }
    else{
        std::cout<<"[ERROR] : File creation failed, Exititng.\n";
        exit(EXIT_FAILURE);
    }
    char buffer[1024] = {};
    int valread = read(newSocketDescriptor, buffer, 1024);
    std::cout<<"[LOG] : Data received "<< valread <<" bytes\n";
    std::cout<<"[LOG] : Saving data to file.\n";
    for (int i = 0; i < valread; i++)
        file.write(buffer + i, 1);
    file.close();
    std::cout<<"[LOG] : File Saved.\n";

    // keyboard_mouse::buttons_coords message;
    // SendInteraction SendM("../../data/received.bin", message);
    // if (SendM.SendIt())
    //     cout << "Error with sending";

    // keyboard_mouse::buttons_coords ReceiveMessage;
    // ReceiveInteraction ReceiveM("../../data/received.bin", ReceiveMessage);
    // ifstream inp;
    // keyboard_mouse::buttons_coords parsed_buttons_coords;

    // if (ReceiveM.ReceiveIt())
    //     cout << "Error wint receiving";
    // ReceiveM.PrintMessage();
}

