#include "Server.h"

int main() {
    Server server(8050, "127.0.0.1");
    server.start();
    int fps = 1;
    std::string filename = "receivedButtonsCoords.bin";
    while (true)
    {
        server.getInteraction();
        usleep(1000.0 / fps);
    }
    return 0;
}