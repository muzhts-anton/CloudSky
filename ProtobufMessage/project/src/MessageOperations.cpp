#include "../include/MessageOperations.h"
using namespace ViktorDev;

KeyboardMouse::ButtonsCoords& InteractionOperations::getMessage()
{
    return message;
}
void InteractionOperations::setMessage(bool buttonPressed[BUTTON_QUANITY], int coords[COORD_QUANITY])
{
    for (int i = 0; i < BUTTON_QUANITY; ++i) {
        getMessage().add_buttonpressed(buttonPressed[i]);
    }
    getMessage().set_xcoord(coords[0]);
    getMessage().set_ycoord(coords[1]);
}
InteractionOperations::InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, string filePath)
{
    getMessage() = myMessage;
    this->filePath = filePath;
};
InteractionOperations::InteractionOperations(bool buttonPressed[BUTTON_QUANITY], int coords[2], string filePath)
{
    setMessage(buttonPressed, coords);
    this->filePath = filePath;
};
InteractionOperations::InteractionOperations()
{
    for (int i = 0; i < BUTTON_QUANITY; ++i) {
        getMessage().add_buttonpressed(false);
    }
    getMessage().set_xcoord(0);
    getMessage().set_ycoord(0);
    this->filePath = "";
};
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
        assert(ERROR_WITH_FILE);
        exit(ERROR_WITH_FILE);
    };
}
SendInteraction::SendInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        cout << "FILE DOES NOT OPENED!" << endl;
        assert(ERROR_WITH_FILE);
        exit(ERROR_WITH_FILE);
    };
};
SendInteraction::~SendInteraction()
{
    out.close();
}
int SendInteraction::sendIt()
{
    ofstream outAddit;
    outAddit.open(filePath, std::ios_base::binary);

    if (!message.SerializePartialToOstream(&outAddit)) {
        //if (!message.SerializePartialToOstream(&out)) {
        cout << "ERRORSEND IT !" << endl;
        return ERROR_SERIALIZE_MESSAGE;
    };
    return SUCCESS;
}

ReceiveInteraction::ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage)
    : InteractionOperations(myMessage, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(ERROR_WITH_FILE);
        exit(ERROR_WITH_FILE);
        in.close();
    };
}
ReceiveInteraction::ReceiveInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2])
    : InteractionOperations(buttonPressed, coords, filePath)
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(ERROR_WITH_FILE);
        exit(ERROR_WITH_FILE);
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
        return ERROR_PARSE_MESSAGE;
    };
    return SUCCESS;
}
