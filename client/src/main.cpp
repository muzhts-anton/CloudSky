#include <iostream>

#include "TCPClientSocket.h"

int main()
{
    TCPClient::TCPClientSocket socket(8050, "127.0.0.2");
    socket.activateSocket();
    int fps = 1;
    std::string file_path = "buttonsCoords.bin";
    while (true)
    {
        socket.transmitFile(file_path);
        usleep(1000.0 / fps);
    }
    return 0;
}
