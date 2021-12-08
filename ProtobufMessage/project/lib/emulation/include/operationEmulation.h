#ifndef OPERATIONEMULATION_H
#define OPERATIONEMULATION_H

#include "../../../../build/project/lib/protobufOperations/KeyboardMouseMessage.pb.h"//#include "messageOperations.h"
#include <cstdlib>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <string>
#include <time.h>

constexpr int buttonQuanity = 9;
constexpr int coordQuanity = 2;
constexpr int mouseButtonsQuanity = 2;

using namespace std;
namespace ViktorDev {
class EmulateInteraction {
public:
    EmulateInteraction();
    ~EmulateInteraction();
    int readInteraction();
    int emulateInteraction(bool* pressedKeys, int coordX, int coordY);
    void emulateMouseMovement();
    void initEmulateMouse();
    void initEmulateKeyboard();
    void initEmulateKbMouse();
    void setKeysCoords(const KeyboardMouse::ButtonsCoords &message);
    void setKeyboard(int keyCode, bool isPressed);
    void synKeyboard();
    void emulateKeyboard(bool* pressedKeys);
    void emulateKeyboard();
    void emulateKbMouse();
    int getCurrentXCoord();
    int getCurrentYCoord();
    bool getCurrentButtonState(char button_symbol);
    void initFD(int kbSet[3]);
    void readFile();

    void printEm();
private:
    int fd;
    struct uinput_user_dev uidev;
    struct input_event ev;
    int coordX, coordY;
    int previousCoordX, previousCoordY;
    int i;


    struct input_event keyInputEvent;
    int fdKeyEmulator;
    struct uinput_user_dev devFakeKeyboard;
    //map();
    int kbSet[buttonQuanity];
// a w s d space q e f esc leftMouseButton rightMouseButton
// 0 1 2 3 4     5 6 7 8   9               10
    bool kbSetBool[buttonQuanity];
    bool mouseButtons[mouseButtonsQuanity];
    FILE* sourceFile;
};

}
#endif  // OPERATIONEMULATION_H