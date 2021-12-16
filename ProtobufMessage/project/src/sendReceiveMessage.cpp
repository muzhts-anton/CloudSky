#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include <fstream>
#include <iostream>

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

    ViktorDev::SendInteraction sendMessageHandler(filePath, message); 
    sendMessageHandler.printMessage();

    std::ofstream out;
    if (sendMessageHandler.sendIt())
        std::cout << "Error with sending";
    KeyboardMouse::ButtonsCoords parsedButtonsCoords;
    ViktorDev::ReceiveInteraction receiveMessangeHandler(filePath, parsedButtonsCoords);

    if (receiveMessangeHandler.receiveIt())
        std::cout << "Error with receiving";
    receiveMessangeHandler.printMessage();
    return SUCCESS;
}
