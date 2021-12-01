#include "Server.h"

int main() {
    Server server(8050, "127.0.0.1");
    server.start();
    double fps = 0.5;
    std::string filename = "receivedButtonsCoords.bin";
    while (true)
    {
        server.getInteraction();
        server.sendFile("fileToSend.bin");
        usleep(1000.0 / fps);
    }
    return 0;
}