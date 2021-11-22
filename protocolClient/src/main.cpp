#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

#include <unistd.h>

int main() {
    TCPClientSocket socket;
    socket.activateSocket();
    int i = 0;
    while (i < 1)//for (int i = 0; i < 1000; i++)
    {
        socket.transmit_file();
        i++;
        //usleep(100000);
    }
    return 0;
}