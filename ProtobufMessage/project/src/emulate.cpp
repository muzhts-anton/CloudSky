#include "KeyboardMouseMessage.pb.h"
#include "operationEmulation.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(true);
    message.add_buttonpressed(true);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.set_xcoord(-50);
    message.set_ycoord(-100);
    message.add_mousebuttons(true);
    message.add_mousebuttons(false);
    
    ViktorDev::EmulateInteraction emulation;
    emulation.setKeysCoords(message);
    emulation.emulateKbMouse();
}