#ifndef MESSAGEOPERATIONS_H
#define MESSAGEOPERATIONS_H

#include "KeyboardMouseMessage.pb.h"
//#include "interactionOperations.h"
//#include "receiveInteraction.h"
//#include "sendInteraction.h"
#include <fstream>
#include <iostream>

using namespace std;
constexpr int BUTTON_QUANITY = 9;
constexpr int COORD_QUANITY = 2;

constexpr int SUCCESS = 0;
constexpr int ERROR_WITH_FILE = 1;
constexpr int ERROR_PARSE_MESSAGE = 2;
constexpr int ERROR_SERIALIZE_MESSAGE = 3;

namespace ViktorDev {
class InteractionOperations {
public:
    KeyboardMouse::ButtonsCoords message;
    KeyboardMouse::ButtonsCoords& getMessage();
    void setMessage(bool buttonPressed[BUTTON_QUANITY], int coords[COORD_QUANITY]);
    InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, string filePath);
    InteractionOperations(bool buttonPressed[BUTTON_QUANITY], int coords[2], string filePath);
    InteractionOperations();
    void printMessage();

protected:
    string filePath;
};

class SendInteraction : public InteractionOperations {
    std::ofstream out;
    int socket;

public:
    SendInteraction() = delete;
    SendInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    SendInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2]);
    ~SendInteraction();
    int sendIt();
};

class ReceiveInteraction : public InteractionOperations {
    std::ifstream in;

public:
    ReceiveInteraction() = delete;
    ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    ReceiveInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2]);
    ~ReceiveInteraction();
    int receiveIt();
};
}
#endif //MESSAGEOPERATIONS_H