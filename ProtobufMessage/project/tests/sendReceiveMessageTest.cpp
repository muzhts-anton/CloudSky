#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include <fstream>
#include <iostream>

int main()
{
    std::string filePath = "buttonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;
    bool pressedButton[buttonQuanity] { false, false, true, true, false, false, false, false, false };
    for (int i = 0; i < buttonQuanity; ++i) {
        message.add_buttonpressed(pressedButton[i]);
    };
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
