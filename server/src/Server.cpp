#include <iostream>
#include <stdexcept>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>

#include "Server.h"
#include "TCPServerSocket.h"
#include "UDPServerSocket.h"
#include "Interactions.h"
#include "SoundComponent.h"
#include "VideoComponent.h"
#include "DataBaseHandler.h"
#include "constants.h"

int main() {
    TCPServerSocket socket;
    socket.receive_file();
    return 0;
}