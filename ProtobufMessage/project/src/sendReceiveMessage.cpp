#include "../include/KeyboardMouseMessage.pb.h"
#include "../include/messageOperations.h"
//#include "../include/operationEmulation.h"
//#include "../include/receiveInteraction.h"
//#include "../include/sendInteraction.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace ViktorDev;
int main()
{
    std::string filePath = "buttonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(true);
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
    //bool arrInit[2] { true, true };
    //int arriInit[2] { 100, 200 };

    SendInteraction sendMessageHandler(filePath, message); 
    sendMessageHandler.printMessage();

    std::ofstream out;
    if (sendMessageHandler.sendIt())
        cout << "Error with sending";
    KeyboardMouse::ButtonsCoords parsedButtonsCoords;
    ReceiveInteraction receiveMessangeHandler(filePath, parsedButtonsCoords);
    //ifstream inp;
    //KeyboardMouse::ButtonsCoords parsedButtonsCoords;

    if (receiveMessangeHandler.receiveIt())
        cout << "Error with receiving";
    receiveMessangeHandler.printMessage();
    //printEm();

    return SUCCESS;
}
