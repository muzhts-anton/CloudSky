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



    


int sending_interaction(std::ofstream& out, std::string file_path, keyboard_mouse::buttons_coords message){
    out.open(file_path, std::ios_base::binary);
    if(!out){
        return error_with_file;
        out.close();
    };
    if(!message.SerializePartialToOstream(&out)){
        return error_serialize_message;
        out.close();
    };
    out.close();
    return success;
}
int receive_interaction(std::ifstream& in, std::string file_path, keyboard_mouse::buttons_coords& parsed_buttons_coords){
    in.open(file_path, std::ios_base::binary);
    if(!in){
        return error_with_file;
        in.close();
    } ;
    if (!parsed_buttons_coords.ParseFromIstream(&in)) {
        return error_parse_message;
        in.close();
    } ;
    in.close();
    return success;
}
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