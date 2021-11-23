#ifndef MessageOperations_H
#define MessageOperations_H

#include "KeyboardMouseMessage.pb.h"
#include <fstream>
#include <iostream>

using namespace std;

#define BUTTON_QUANITY 9
#define COORD_QUANITY 2

#define SUCCESS 0
#define ERROR_WITH_FILE 1
#define ERROR_PARSE_MESSAGE 2
#define ERROR_SERIALIZE_MESSAGE 3

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
    InteractionOperations(myMessage);
    SendInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2]);
    ~SendInteraction();
    int sendIt();
};

class ReceiveInteraction : public InteractionOperations {
    std::ifstream in;

public:
    ReceiveInteraction() = delete;
    ReceiveInteraction(std::string filePath, KeyboardMouse::ButtonsCoords myMessage);
    InteractionOperations(myMessage);
    ReceiveInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2]);
    ~ReceiveInteraction();
    int receiveIt();
};

#endif