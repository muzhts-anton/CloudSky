#include "../include/messageOperations.h"

using namespace ViktorDev;

KeyboardMouse::ButtonsCoords& InteractionOperations::getMessage()
{
    return message;
}
void InteractionOperations::setMessage(bool buttonPressed[buttonQuanity], int coords[coordQuanity])
{
    for (int i = 0; i < buttonQuanity; ++i) {
        getMessage().add_buttonpressed(buttonPressed[i]);
    }
    getMessage().set_xcoord(coords[0]);
    getMessage().set_ycoord(coords[1]);
}
InteractionOperations::InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, string filePath)
{
    getMessage() = myMessage;
    this->filePath = filePath;
}
InteractionOperations::InteractionOperations(bool buttonPressed[buttonQuanity], int coords[2], string filePath)
{
    setMessage(buttonPressed, coords);
    this->filePath = filePath;
}
InteractionOperations::InteractionOperations()
{
    for (int i = 0; i < buttonQuanity; ++i) {
        getMessage().add_buttonpressed(false);
    }
    getMessage().set_xcoord(0);
    getMessage().set_ycoord(0);
    this->filePath = "";
}
void InteractionOperations::printMessage()
{
    cout << "Pressed buttons: ";
    for (const bool& button : getMessage().buttonpressed()) {
        cout << button << " ";
    };
    cout << endl;
    cout << "xCoord = " << getMessage().xcoord() << endl;
    cout << "yCoord = " << getMessage().ycoord() << endl;
}

SendInteraction::SendInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage)
    : InteractionOperations(myMessage, filePath)
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        cout << "FILE DOES NOT OPENED!" << endl;
        assert(errorWithFile);
        exit(errorWithFile);
    };
}
SendInteraction::SendInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        cout << "FILE DOES NOT OPENED!" << endl;
        assert(errorWithFile);
        exit(errorWithFile);
    };
}
SendInteraction::~SendInteraction()
{
    out.close();
}
int SendInteraction::sendIt()
{
    ofstream outAddit;
    outAddit.open(filePath, std::ios_base::binary);

    if (!message.SerializePartialToOstream(&outAddit)) {
        cout << "ERRORSEND IT !" << endl;
        return errorSerializeMessage;
    };
    return SUCCESS;
}

ReceiveInteraction::ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage)
    : InteractionOperations(myMessage, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        cout<<"errorWithFile in ReceiveInteraction constructor";
        assert(errorWithFile);
        exit(errorWithFile);
        in.close();
    };
}
ReceiveInteraction::ReceiveInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        exit(errorWithFile);
        in.close();
    };
}
ReceiveInteraction::~ReceiveInteraction()
{
    in.close();
}
int ReceiveInteraction::receiveIt()
{
    if (!message.ParseFromIstream(&in)) {
        return errorParseMessage;
    };
    return SUCCESS;
}