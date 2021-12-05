#include "Worker.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;
    Worker worker(argv[1], argv[2]);
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