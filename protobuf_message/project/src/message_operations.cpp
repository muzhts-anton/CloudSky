#include "../include/message_operations.h"




    keyboard_mouse::buttons_coords& InteractionOperations::GetMessage (){
        return message;
    }
    void InteractionOperations::SetMessage(bool button_pressed[button_quanity], int coords[coord_quanity]){
        for (int i = 0; i < button_quanity; ++i) {
            GetMessage().add_button_pressed(button_pressed[i]);
        }
        GetMessage().set_x_coord(coords[0]);
        GetMessage().set_y_coord(coords[1]);
    }
    InteractionOperations::InteractionOperations(keyboard_mouse::buttons_coords message_1){
        GetMessage() = message_1;
    };
    InteractionOperations::InteractionOperations(bool button_pressed[button_quanity], int coords[2]){
        SetMessage(button_pressed, coords);
    };
    InteractionOperations::InteractionOperations(){
        for (int i = 0; i < button_quanity; ++i) {
            GetMessage().add_button_pressed(false);
        }
        GetMessage().set_x_coord(0);
        GetMessage().set_y_coord(0);
    };
    void InteractionOperations::PrintMessage(){
        cout<< "Pressed buttons: ";
        for(const bool &button : GetMessage().button_pressed()){
            cout<<button<<" ";
        };
        cout<<endl;
        cout<<"x_coord = "<<GetMessage().x_coord()<<endl;
        cout<<"y_coord = "<<GetMessage().y_coord()<<endl;
    }



    SendInteraction::SendInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1): 
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
    SendInteraction::SendInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]):
     InteractionOperations(button_pressed, coords){
        out.open(file_path, std::ios_base::binary);
        if(!out){
            cout<<"FILE DOES NOT OPENED!"<<endl;
            assert(error_with_file);
            exit(error_with_file);
        };
    };
    SendInteraction::~SendInteraction(){
        out.close();
    }
    int SendInteraction::SendIt(){
        ofstream out_addit;
        out_addit.open("buttons_coords.bin", std::ios_base::binary);

        if(!message.SerializePartialToOstream(&out_addit)){
            cout<<"ERRORSEND IT !"<<endl;
            return error_serialize_message;
        };
        return success;
    }




    ReceiveInteraction::ReceiveInteraction(std::string file_path, keyboard_mouse::buttons_coords message_1): 
    InteractionOperations(message_1){
        //GetMessage() = message_1;
        in.open(file_path, std::ios_base::binary);
        if(!in){
            assert(error_with_file);
            exit(error_with_file);
            in.close();
        };
    }
    ReceiveInteraction::ReceiveInteraction(std::string file_path, bool button_pressed[button_quanity], int coords[2]): InteractionOperations(button_pressed, coords){
        in.open(file_path, std::ios_base::binary);
        if(!in){
            assert(error_with_file);
            exit(error_with_file);
            in.close();
        };
        //SetMessage(button_pressed, coords);
    }
    ReceiveInteraction::~ReceiveInteraction(){
        in.close();
    }
    int ReceiveInteraction::ReceiveIt(){
        if (!message.ParseFromIstream(&in)) {
            return error_parse_message;
        };
        return success;
    }
