#include "TCPClientSocket.h"
#include "UDPClientSocket.h"

int main() {
    TCPClientSocket socket;
    socket.transmit_file();
    return 0;
}