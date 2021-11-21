#include<iostream>
#include <fstream>
#include "keyboard_mouse_message.pb.h"

#pragma once
using namespace std;

#define button_quanity 3
#define coord_quanity 2

#define success 0
#define error_with_file 1
#define error_parse_message 2
#define error_serialize_message 3



class InteractionOperations{
    public:
    keyboard_mouse::buttons_coords message;
    keyboard_mouse::buttons_coords& GetMessage ();
    void SetMessage(bool button_pressed[button_quanity], int coords[coord_quanity]);
    InteractionOperations(keyboard_mouse::buttons_coords message_1);
    InteractionOperations(bool button_pressed[button_quanity], int coords[2]);
    InteractionOperations();
    void PrintMessage();
};

class SendInteraction: public InteractionOperations{ 
    std::ofstream out;
    int socket;
    public:
    SendInteraction() = delete;
    SendInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1);
    InteractionOperations(message_1);
    SendInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]); 
    ~SendInteraction();
    int SendIt();
};

class ReceiveInteraction: public InteractionOperations{ 
    std::ifstream in;
    public:
    ReceiveInteraction() = delete;
    ReceiveInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1);
    InteractionOperations(message_1);
    ReceiveInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]); 
    ~ReceiveInteraction();
    int ReceiveIt();
};


