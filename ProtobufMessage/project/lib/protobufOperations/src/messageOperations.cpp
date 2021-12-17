#include "messageOperations.h"

KeyboardMouse::ButtonsCoords& ViktorDev::InteractionOperations::getMessage()
{
    return message;
}
void ViktorDev::InteractionOperations::setMessage(bool buttonPressed[buttonQuanity], int coords[coordQuanity])
{
    for (int i = 0; i < buttonQuanity; ++i) {
        getMessage().add_buttonpressed(buttonPressed[i]);
    }
    getMessage().set_xcoord(coords[0]);
    getMessage().set_ycoord(coords[1]);
}
ViktorDev::InteractionOperations::InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, std::string filePath)
{
    getMessage() = myMessage;
    this->filePath = filePath;
}
ViktorDev::InteractionOperations::InteractionOperations(bool buttonPressed[buttonQuanity], int coords[2], std::string filePath)
{
    setMessage(buttonPressed, coords);
    this->filePath = filePath;
}
ViktorDev::InteractionOperations::InteractionOperations()
{
    for (int i = 0; i < buttonQuanity; ++i) {
        getMessage().add_buttonpressed(false);
    }
    getMessage().set_xcoord(0);
    getMessage().set_ycoord(0);
    this->filePath = "";
}
void ViktorDev::InteractionOperations::printMessage()
{
    std::cout << "Pressed buttons: ";
    for (const bool& button : getMessage().buttonpressed()) {
        std::cout << button << " ";
    };
    std::cout << std::endl;
    std::cout << "xCoord = " << getMessage().xcoord() << std::endl;
    std::cout << "yCoord = " << getMessage().ycoord() << std::endl;
}

ViktorDev::SendInteraction::SendInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage)
    : InteractionOperations(myMessage, filePath)
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(errorWithFile);
        exit(errorWithFile);
    };
}
ViktorDev::SendInteraction::SendInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(errorWithFile);
        exit(errorWithFile);
    };
}
ViktorDev::SendInteraction::~SendInteraction()
{
    out.close();
}
int ViktorDev::SendInteraction::sendIt()
{
    std::ofstream outAddit;
    outAddit.open(filePath, std::ios_base::binary);

    if (!message.SerializePartialToOstream(&outAddit)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return errorSerializeMessage;
    };
    outAddit.close();
    return SUCCESS;
}

ViktorDev::ReceiveInteraction::ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage)
    : InteractionOperations(myMessage, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        std::cout << "errorWithFile in ReceiveInteraction constructor";
        assert(errorWithFile);
        exit(errorWithFile);
        in.close();
    };
}
ViktorDev::ReceiveInteraction::ReceiveInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        exit(errorWithFile);
        in.close();
    };
}
ViktorDev::ReceiveInteraction::~ReceiveInteraction()
{
    in.close();
}
int ViktorDev::ReceiveInteraction::receiveIt()
{
    if (!message.ParseFromIstream(&in)) {
        return errorParseMessage;
    };
    return SUCCESS;
}