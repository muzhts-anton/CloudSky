#include "Worker.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include "operationEmulation.h"
#include "ScreenRecorder.h"

using namespace ViktorDev;

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;
    Worker worker(argv[1], argv[2]);
    KeyboardMouse::ButtonsCoords ReceiveMessage;
    EmulateInteraction emulation;
    ScreenRecorder recorder;
    
    emulation.initEmulateKbMouse();
    worker.start();
    double fps = 0.5;
    std::string filename = "receivedButtonsCoords.bin";
    std::string videoFilename = "out.mp4";
    while (true)
    {
        std::cout << "Отлавливаем...\n";
        recorder.Start();
        std::cout << "Отловили?\n";
        worker.getInteraction(filename);
        ReceiveInteraction ReceiveM(filename, ReceiveMessage);

        if (ReceiveM.receiveIt(filename))
            std::cout << "Error wint receiving";
        ReceiveM.printMessage();
        emulation.setKeysCoords(ReceiveM.getMessage());
        emulation.emulateKbMouse();
        //worker.sendFile(videoFilename);
        usleep(1000.0 / fps);
    }
    recorder.Stop();
    return 0;
}