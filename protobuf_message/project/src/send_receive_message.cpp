#include<iostream>
#include <fstream>
#include "../include/keyboard_mouse_message.pb.h"
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
    //std::fstream stream;
    keyboard_mouse::buttons_coords& GetMessage (){
        return message;
    }
    void SetMessage(bool button_pressed[button_quanity], int coords[coord_quanity]){
        for (int i = 0; i < button_quanity; ++i) {
            GetMessage().add_button_pressed(button_pressed[i]);
        }
        GetMessage().set_x_coord(coords[0]);
        GetMessage().set_y_coord(coords[1]);
    }
    InteractionOperations(keyboard_mouse::buttons_coords message_1){
        GetMessage() = message_1;
    };
    InteractionOperations(bool button_pressed[button_quanity], int coords[2]){
        SetMessage(button_pressed, coords);
    };
    void PrintMessage(){
        cout<< "Pressed buttons: ";
        for(const bool &button : GetMessage().button_pressed()){
            cout<<button<<" ";
        };
        cout<<endl;
        cout<<"x_coord = "<<GetMessage().x_coord()<<endl;
        cout<<"y_coord = "<<GetMessage().y_coord()<<endl;
    }
};

class SendInteraction: public InteractionOperations{ // send_interaction
    std::ofstream out;
    public:
    SendInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1): 
    InteractionOperations(message_1){
        //GetMessage() = message_1;
        out.open(file_path, std::ios_base::binary);
        if(!out){
            cout<<"FILE DOES NOT OPENED!"<<endl;
            assert(error_with_file);
            exit(error_with_file);
            //out.close();
        };
    }
    SendInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]): InteractionOperations(button_pressed, coords){
        out.open(file_path, std::ios_base::binary);
        if(!out){
            cout<<"FILE DOES NOT OPENED!"<<endl;
            assert(error_with_file);
            exit(error_with_file);
            //out.close();
        };
        //SetMessage(button_pressed, coords);
    }
    ~SendInteraction(){
        out.close();
    }
    int SendIt(){
        ofstream out_addit;
        out_addit.open("buttons_coords.bin", std::ios_base::binary);

        if(!message.SerializePartialToOstream(&out_addit)){
            cout<<"ERRORSEND IT !"<<endl;
            return error_serialize_message;
        };
        return success;
    }
};

class ReceiveInteraction: public InteractionOperations{ // send_interaction
    std::ifstream in;
    public:
    ReceiveInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1): 
    InteractionOperations(message_1){
        //GetMessage() = message_1;
        in.open(file_path, std::ios_base::binary);
        if(!in){
            assert(error_with_file);
            exit(error_with_file);
            in.close();
        };
    }
    ReceiveInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]): InteractionOperations(button_pressed, coords){
        in.open(file_path, std::ios_base::binary);
        if(!in){
            assert(error_with_file);
            exit(error_with_file);
            in.close();
        };
        //SetMessage(button_pressed, coords);
    }
    ~ReceiveInteraction(){
        in.close();
    }
    int ReceiveIt(){
    if (!message.ParseFromIstream(&in)) {
        return error_parse_message;
    };
    return success;
    }
};

int reading_interaction(FILE *interaction_file, keyboard_mouse::buttons_coords& message){ // reading interaction from file
    
}

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

    //SendInteraction SendM(file_path, message);
    SendInteraction SendM(file_path, message);
    SendM.PrintMessage();
    //send_interaction send_mes(file_path, message);

    std::ofstream out;
    //int result = sending_interaction(out, file_path, message);
    if (SendM.SendIt()) cout<<"Error with sending";

    keyboard_mouse::buttons_coords ReceiveMessage;
    ReceiveInteraction ReceiveM(file_path, ReceiveMessage);
    ifstream inp;
    keyboard_mouse::buttons_coords parsed_buttons_coords;
    //result = receive_interaction((inp), file_path, parsed_buttons_coords);
    //cout<<"Func receive x_coord = "<<parsed_buttons_coords.x_coord()<<endl;
    if(ReceiveM.ReceiveIt()) cout<<"Error wint receiving";
    ReceiveM.PrintMessage();

    return success;
}