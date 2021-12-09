#include "../../../../build/project/lib/protobufOperations/KeyboardMouseMessage.pb.h"
#include "../include/messageOperations.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace ViktorDev;
int main()
{
    std::string filePath = "buttonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.set_xcoord(5);
    message.set_ycoord(10);
    message.add_mousebuttons(true);
    message.add_mousebuttons(true);

    SendInteraction sendMessageHandler(filePath, message); 
    sendMessageHandler.printMessage();

    std::ofstream out;
    if (sendMessageHandler.sendIt())
        cout << "Error with sending";
    KeyboardMouse::ButtonsCoords parsedButtonsCoords;
    ReceiveInteraction receiveMessangeHandler(filePath, parsedButtonsCoords);

    if (receiveMessangeHandler.receiveIt())
        cout << "Error with receiving";
    receiveMessangeHandler.printMessage();
    return SUCCESS;
}
