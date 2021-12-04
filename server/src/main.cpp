#include "Server.h"

int main()
{
    Server server(8050, "0.0.0.0");
    server.start();
    //server.startNewWorker();
    double fps = 0.5;
    std::string fileToReceivePath = "receivedButtonsCoords.bin";
    while (true) {
        server.getInteraction(fileToReceivePath);
        server.sendFile("fileToSend.bin");
        usleep(1000.0 / fps);
    }
    return 0;
}