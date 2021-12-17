#ifndef OPERATIONEMULATION_H
#define OPERATIONEMULATION_H

#include "KeyboardMouseMessage.pb.h"
#include "emulationConstants.h"
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

namespace ViktorDev {

class EmelationKeyBoard {
public:
    EmelationKeyBoard();
    void initKeyboard(uinput_user_dev& devFakeKeyboard);
    void initEmulateKeyboard();
    void setKeyboard(const KeyboardMouse::ButtonsCoords& message);
    void synKeyboard();
    void emulateKeyboard();
    bool getCurrentButtonState(char symbol);
private:
    struct input_event keyInputEvent;
    int fdKeyEmulator;
    std::vector<std::pair<int, bool>> pressedButtons;
    int kbEncoding[buttonQuanity] { KEY_A, KEY_W, KEY_S, KEY_D, KEY_SPACE, KEY_Q, KEY_E, KEY_F, KEY_ESC };
    // a w s d space q e f esc
    // 0 1 2 3 4     5 6 7 8
};

class EmulationMouse {
public:
    EmulationMouse();
    void initEmulateMouse();
    void setCoordsButtons(const KeyboardMouse::ButtonsCoords& message);
    void emulateMouse();
    void emulateMouseMovement(int coordX, int coordY);
    void emulateMouseButtons(std::vector<std::pair<int, bool>> mouseButton);
    void synMouse();
    int getCurrentXCoord();
    int getCurrentYCoord();


private:
    std::pair<int, int> coords, previousCoords;
    std::vector<std::pair<int, bool>> mouseButtons;
    int fdMouse;
    struct uinput_user_dev uidev;
    struct input_event event;
};

}
#endif // OPERATIONEMULATION_H