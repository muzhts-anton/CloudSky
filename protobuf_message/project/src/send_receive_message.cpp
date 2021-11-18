#include<iostream>
#include <fstream>
#include "../include/keyboard_mouse_message.pb.h"
#include "../include/message_operations.h"
using namespace std;

#define button_quanity 3
#define coord_quanity 2


#define success 0
#define error_with_file 1
#define error_parse_message 2
#define error_serialize_message 3



int main(){
    std::string file_path = "buttons_coords.bin";
    keyboard_mouse::buttons_coords message;
    message.add_button_pressed(true);
    message.add_button_pressed(false);
    message.set_x_coord(5);
    message.set_y_coord(10);
    bool arr_init[2]{true,true};
    int arri_init[2]{100,200};


    SendInteraction SendM(file_path, message);
    SendM.PrintMessage();

    std::ofstream out;
    if (SendM.SendIt()) cout<<"Error with sending";

    keyboard_mouse::buttons_coords ReceiveMessage;
    ReceiveInteraction ReceiveM(file_path, ReceiveMessage);
    ifstream inp;
    keyboard_mouse::buttons_coords parsed_buttons_coords;

    if(ReceiveM.ReceiveIt()) cout<<"Error wint receiving";
    ReceiveM.PrintMessage();

    return success;
}