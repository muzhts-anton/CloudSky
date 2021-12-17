#ifndef MESSAGEOPERATIONS_H
#define MESSAGEOPERATIONS_H

#include "KeyboardMouseMessage.pb.h"
#include "messageConstants.h"
#include <fstream>
#include <iostream>


namespace ViktorDev {
class InteractionOperations {
public:
    KeyboardMouse::ButtonsCoords message;
    KeyboardMouse::ButtonsCoords& getMessage();
    void setMessage(bool buttonPressed[buttonQuanity], int coords[coordQuanity]);
    InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, std::string filePath);
    InteractionOperations(bool buttonPressed[buttonQuanity], int coords[coordQuanity], std::string filePath);
    InteractionOperations();
    void printMessage();

protected:
    std::string filePath;
};

class SendInteraction : public InteractionOperations {
    std::ofstream out;

public:
    SendInteraction() = delete;
    SendInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    SendInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[coordQuanity]);
    ~SendInteraction();
    int sendIt();
};

class ReceiveInteraction : public InteractionOperations {
    std::ifstream in;

public:
    ReceiveInteraction() = delete;
    ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    ReceiveInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[coordQuanity]);
    ~ReceiveInteraction();
    int receiveIt();
};
}
#endif //MESSAGEOPERATIONS_H