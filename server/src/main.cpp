#include "Server.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"

int main() {
    Server server(8050, "127.0.0.2");
    server.start();
    int fps = 40;
    std::string filename = "receivedButtonsCoords.bin";
    while (true)
    {
        server.getInteraction();
        KeyboardMouse::ButtonsCoords ReceiveMessage;
        ViktorDev::ReceiveInteraction ReceiveM(filename, ReceiveMessage);

        if (ReceiveM.receiveIt(filename))
            cout << "Error wint receiving";
        ReceiveM.printMessage();

        usleep(1000.0 / fps);
    }
    return 0;
}