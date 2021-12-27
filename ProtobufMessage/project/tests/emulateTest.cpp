#include "KeyboardMouseMessage.pb.h"
#include "operationEmulation.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    KeyboardMouse::ButtonsCoords message;
    bool pressedButton[buttonQuanityEm] { false, false, true, true, false, false, false, false, false };
    for (int i = 0; i < buttonQuanityEm; ++i) {
        message.add_buttonpressed(pressedButton[i]);
    };

    message.set_xcoord(-500);
    message.set_ycoord(-1000);
    message.add_mousebuttons(false);
    message.add_mousebuttons(true);

    ViktorDev::EmelationKeyBoard kbEmulation;
    kbEmulation.setKeyboard(message);
    kbEmulation.emulateKeyboard();

    ViktorDev::EmulationMouse mouseEmulation;
    mouseEmulation.setCoordsButtons(message);
    for(int i = 0; i <10; ++i){
        mouseEmulation.emulateMouse();
    }
}