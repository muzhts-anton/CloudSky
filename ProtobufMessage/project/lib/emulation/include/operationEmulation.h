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
    input_event& getKeyInputEvent();
    int& getFdKeyEmulator();
    bool getCurrentButtonState(char button_symbol);
    void initFD(int kbSet[3]);
    void readFile();
    void printEm();
     //{ move to private
    //     {KEY_A, false},
    //     {KEY_W, false},
    //     {KEY_S, false},
    //     {KEY_D, false},
    //     {KEY_SPACE, false},
    //     {KEY_Q, false},
    //     {KEY_E, false},
    //     {KEY_F, false},
    //     {KEY_ESC, false}
    // };
private:
    int fd;
    struct uinput_user_dev uidev;
    struct input_event ev;
    vector<pair<int, bool>> encoding;
    pair<int,int> coords, previousCoords;
    
    //int i;


    struct input_event keyInputEvent;
    int fdKeyEmulator;
    struct uinput_user_dev devFakeKeyboard;

    // map<char, bool> encoding = {
    //     {'a', KEY_A},
    //     {'w', KEY_W},
    //     {'s', KEY_S},
    //     {'d', KEY_D},
    //     {' ', KEY_SPACE},
    //     {'q', KEY_Q},
    //     {'e', KEY_E},
    //     {'f', KEY_F},
    //     {'`', KEY_ESC}
    // };
    //int kbSet[buttonQuanity];
// a w s d space q e f esc
// 0 1 2 3 4     5 6 7 8   
    //bool kbSetBool[buttonQuanity];
    vector<pair<int, bool>> mouseButtons;
    //bool mouseButtons[mouseButtonsQuanity];
    FILE* sourceFile;
};

}
#endif  // OPERATIONEMULATION_H