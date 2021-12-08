#include "../../../../build/project/lib/protobufOperations/KeyboardMouseMessage.pb.h"
//#include "../include/KeyboardMouseMessage.pb.h"
//#include "../include/messageOperations.h"
#include "../include/operationEmulation.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace ViktorDev;

int main(int argc, char** argv)
{
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.set_xcoord(-50);
    message.set_ycoord(-100);
    message.add_mousebuttons(true);
    message.add_mousebuttons(true);
    
    EmulateInteraction emulation;
    //emulation.initEmulateKbMouse();
    emulation.setKeysCoords(message);
    emulation.emulateKbMouse();

}