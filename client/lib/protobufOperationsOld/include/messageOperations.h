#ifndef MESSAGEOPERATIONS_H
#define MESSAGEOPERATIONS_H

#include "KeyboardMouseMessage.pb.h"
//#include "interactionOperations.h"
//#include "receiveInteraction.h"
//#include "sendInteraction.h"
#include <fstream>
#include <iostream>

using namespace std;
constexpr int buttonQuanity = 9;
constexpr int coordQuanity = 2;

constexpr int SUCCESS = 0;
constexpr int errorWithFile = 1;
constexpr int errorParseMessage = 2;
constexpr int errorSerializeMessage = 3;


namespace ViktorDev {
class InteractionOperations {
public:
    KeyboardMouse::ButtonsCoords message;
    KeyboardMouse::ButtonsCoords& getMessage();
    void setMessage(bool buttonPressed[buttonQuanity], int coords[coordQuanity]);
    InteractionOperations(KeyboardMouse::ButtonsCoords myMessage, string filePath);
    InteractionOperations(bool buttonPressed[buttonQuanity], int coords[2], string filePath);
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
    //InteractionOperations(myMessage);
    SendInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2]);
    ~SendInteraction();
    int sendIt();
};

class ReceiveInteraction : public InteractionOperations {
    std::ifstream in;

public:
    ReceiveInteraction() = delete;
    ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    //InteractionOperations(myMessage);
    ReceiveInteraction(std::string filePath, bool buttonPressed[buttonQuanity], int coords[2]);
    ~ReceiveInteraction();
    int receiveIt(std::string filePath);
};
}
#endif //MESSAGEOPERATIONS_H