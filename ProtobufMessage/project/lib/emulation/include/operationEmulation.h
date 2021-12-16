#ifndef OPERATIONEMULATION_H
#define OPERATIONEMULATION_H

#include "KeyboardMouseMessage.pb.h"
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

#include <string>
#include <time.h>

constexpr int buttonQuanity = 9;
constexpr int coordQuanity = 2;
constexpr int mouseButtonsQuanity = 2;

namespace ViktorDev {
class EmulateInteraction {
public:
    EmulateInteraction();
    ~EmulateInteraction();
    void emulateMouseMovement();
    void initEmulateMouse();
    void initEmulateKeyboard();
    void initEmulateKbMouse();
    void setKeysCoords(const KeyboardMouse::ButtonsCoords &message);
    void setKeyboard(int keyCode, bool isPressed);
    void synKeyboard();
    void emulateKeyboard();
    void emulateKbMouse();
    input_event& getKeyInputEvent();
    int& getFdKeyEmulator();

private:
    int fd;
    struct uinput_user_dev uidev;
    struct input_event ev;
    std::vector<std::pair<int, bool>> encoding;
    std::pair<int,int> coords, previousCoords;

    struct input_event keyInputEvent;
    int fdKeyEmulator;
    struct uinput_user_dev devFakeKeyboard;
    //int kbSet[buttonQuanity];
// a w s d space q e f esc
// 0 1 2 3 4     5 6 7 8   
    std::vector<std::pair<int, bool>> mouseButtons;
    FILE* sourceFile;
};

}
#endif  // OPERATIONEMULATION_H