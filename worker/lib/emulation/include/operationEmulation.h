#ifndef OPERATIONEMULATION_H
#define OPERATIONEMULATION_H

#include "KeyboardMouseMessage.pb.h"//#include "messageOperations.h"
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

constexpr int buttonQuanityEm = 9;
constexpr int coordQuanityEm = 2;
constexpr int mouseButtonsQuanityEm = 2;

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
    input_event& getKeyInputEvent();
    int& getFdKeyEmulator();
    bool getCurrentButtonState(char button_symbol);
    void initFD(int kbSet[3]);
    void readFile();
    void printEm();

private:
    int fd;
    struct uinput_user_dev uidev;
    struct input_event ev;
    vector<pair<int, bool>> encoding;
    pair<int,int> coords, previousCoords;

    struct input_event keyInputEvent;
    int fdKeyEmulator;
    struct uinput_user_dev devFakeKeyboard;
    //int kbSet[buttonQuanity];
// a w s d space q e f esc
// 0 1 2 3 4     5 6 7 8   
    vector<pair<int, bool>> mouseButtons;
    FILE* sourceFile;
};

}
#endif  // OPERATIONEMULATION_H