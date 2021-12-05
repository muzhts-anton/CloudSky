#include "Worker.h"

int main()
{
    Worker worker(8050, "0.0.0.0");
    worker.start();
    double fps = 0.5;
    std::string fileToReceivePath = "receivedButtonsCoords.bin";
    while (true) {
        worker.getInteraction(fileToReceivePath);
        worker.sendFile("fileToSend.bin");
        usleep(1000.0 / fps);
    }
    return 0;
}