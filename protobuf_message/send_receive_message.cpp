#include<iostream>
#include <fstream>
#include "keyboard_mouse_message.pb.h"
using namespace std;

int main(){
    keyboard_mouse::buttons_coords message;
    message.add_button_pressed(true);
    message.add_button_pressed(false);
    message.add_button_pressed(true);
    message.set_x_coord(5);
    message.set_y_coord(10);

    std::ofstream out("buttons_coords.bin", std::ios_base::binary);
    message.SerializePartialToOstream(&out);
    out.close();

    ifstream inp("buttons_coords.bin",std::ios_base::binary);
    keyboard_mouse::buttons_coords parsed_buttons_coords;

    if (parsed_buttons_coords.ParseFromIstream(&inp)){
        cout<< "Pressed buttons: ";
        for(const bool &button : parsed_buttons_coords.button_pressed()){
            cout<<button<<" ";
        };
        cout<<endl;
        cout<<"x_coord = "<<parsed_buttons_coords.x_coord()<<endl;
        cout<<"y_coord = "<<parsed_buttons_coords.y_coord()<<endl;
    }
    else{
        cout<<"Failed to parse message\n";
    }
    inp.close();
    return 0;
}