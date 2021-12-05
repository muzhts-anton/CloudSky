#include "Worker.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include "operationEmulation.h"

using namespace ViktorDev;

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;
    Worker worker(argv[1], argv[2]);
    KeyboardMouse::ButtonsCoords ReceiveMessage;
    EmulateInteraction emulation;
    emulation.initEmulateKbMouse();
    worker.start();
    double fps = 0.5;
    std::string filename = "receivedButtonsCoords.bin";
    while (true)
    {
        worker.getInteraction(filename);
        ReceiveInteraction ReceiveM(filename, ReceiveMessage);

        if (ReceiveM.receiveIt(filename))
            cout << "Error wint receiving";
        ReceiveM.printMessage();
        emulation.setKeysCoords(ReceiveM.getMessage());
        emulation.emulateKbMouse();
        usleep(1000.0 / fps);
    }
    return 0;
}