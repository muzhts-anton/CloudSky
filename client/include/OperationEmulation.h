#ifndef OperationEmulation_H
#define OperationEmulation_H

#include "MessageOperations.h"
#include <cstdlib>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <time.h>
namespace ViktorDev {
class EmulateInteraction : public ReceiveInteraction {
public:
    EmulateInteraction(std::string filePath, KeyboardMouse::ButtonsCoords message);
    EmulateInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2]);
    ~EmulateInteraction();
    int readInteraction();
    int emulateInteraction(bool* pressedKeys, int coordX, int coordY);
    void emulateMouseMovement(int coordX, int coordY);
    void emulateKeyboard(bool* pressedKeys);
    int getCurrentXCoord();
    int getCurrentYCoord();
    bool getCurrentButtonState(char button_symbol);
    void initFD(int kb_set[3]);
    void readFile();
    void emulateKeyboard();

private:
    struct input_event keyInputEvent;
    int fdKeyEmulator;
    struct uinput_user_dev devFakeKeyboard;
    int kb_set[3];
    bool kbSetBool[3];
    FILE* sourceFile;
};

// class EmulateInteraction : public ReceiveInteraction {
// public:
//     EmulateInteraction(std::string filePath, KeyboardMouse::ButtonsCoords message)
//         : ReceiveInteraction(filePath, message) {

//         };
//     EmulateInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2])
//         : ReceiveInteraction(filePath, buttonPressed, coords) {

//         };
//     ~EmulateInteraction() {

//     };
//     int readInteraction() {

//     };
//     int emulateInteraction(bool* pressedKeys, int coordX, int coordY) {

//     };
//     void emulateMouseMovement(int coordX, int coordY) {

//     };
//     void emulateKeyboard(bool* pressedKeys) {

//     };
//     int getCurrentXCoord() {

//     };
//     int getCurrentYCoord() {

//     };
//     bool getCurrentButtonState(char button_symbol) {

//     };
// };
}
#endif