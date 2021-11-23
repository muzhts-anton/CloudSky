#include "../include/KeyboardMouseMessage.pb.h"
#include "../include/MessageOperations.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{

    std::string filePath = "ButtonsCoords1.bin";
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(true);
    message.add_buttonpressed(false);
    message.set_xcoord(5);
    message.set_ycoord(10);
    bool arrInit[2] { true, true };
    int arriInit[2] { 100, 200 };

    SendInteraction sendMessageHandler(filePath, message);
    sendMessageHandler.printMessage();

    std::ofstream out;
    if (sendMessageHandler.sendIt())
        cout << "Error with sending";
    KeyboardMouse::ButtonsCoords receiveMessageHandler;
    ReceiveInteraction receiveMessangeHandler(filePath, receiveMessageHandler);
    ifstream inp;
    KeyboardMouse::ButtonsCoords parsedButtonsCoords;

    if (receiveMessangeHandler.receiveIt())
        cout << "Error wint receiving";
    receiveMessangeHandler.printMessage();

    return SUCCESS;
}