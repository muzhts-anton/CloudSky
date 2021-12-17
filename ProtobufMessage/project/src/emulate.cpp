#include "KeyboardMouseMessage.pb.h"
#include "operationEmulation.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    KeyboardMouse::ButtonsCoords message;
    bool pressedButton[buttonQuanity]{false,false,true,true,false,false,false,false,false};
    for(int i = 0; i < buttonQuanity; ++i){
        message.add_buttonpressed(pressedButton[i]);
    };
    message.set_xcoord(-50);
    message.set_ycoord(-100);
    message.add_mousebuttons(false);
    message.add_mousebuttons(true);
    
    ViktorDev::EmelationKeyBoard kbEmulation;
    kbEmulation.setKeyboard(message);
    kbEmulation.emulateKeyboard();

    ViktorDev::EmulationMouse mouseEmulation;
    mouseEmulation.setCoordsButtons(message);
    mouseEmulation.emulateMouse();

}