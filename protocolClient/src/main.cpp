#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

#include <unistd.h>

int main() {
    TCPClientSocket socket;
    socket.activateSocket();
    int fps = 40;
    while (true)
    {
        socket.transmit_file();
        usleep(1000.0 / fps);
    }
    return 0;
}