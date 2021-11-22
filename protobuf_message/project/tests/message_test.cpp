#include <gtest/gtest.h>

#include "../include/message_operations.h"

TEST(MESSAGE_TEST, constructor_message_test) {
    keyboard_mouse::buttons_coords message;
    bool ButtonSeq[button_quanity]{true,false,false};
    for(int i = 0; i < 3; ++i){
        message.add_button_pressed(ButtonSeq[i]);
    }
    int coords[coord_quanity]{2, 45};
    for(int i = 0; i < 2; ++i){
        message.set_x_coord(coords[i]);
    }
    InteractionOperations InterOp(message);
    int  i = 0;
    for(const bool &button :InterOp.GetMessage().button_pressed()){
        EXPECT_EQ(ButtonSeq[i], button);
        ++i;
    };
    EXPECT_EQ(InterOp.GetMessage().x_coord(), coords[0]);
    EXPECT_EQ(InterOp.GetMessage().y_coord(), coords[1]);
}

TEST(MESSAGE_TEST, constructor_coords_test) {
    bool ButtonSeq[button_quanity]{true,false,false};
    int coords[coord_quanity]{2, 45};
    InteractionOperations InterOp(ButtonSeq, coords);
    int  i = 0;
    for(const bool &button :InterOp.GetMessage().button_pressed()){
        EXPECT_EQ(ButtonSeq[i], button);
        ++i;
    };
    EXPECT_EQ(InterOp.GetMessage().x_coord(), coords[0]);
    EXPECT_EQ(InterOp.GetMessage().y_coord(), coords[1]);
}

TEST(MESSAGE_TEST, default_constructor_test) {
    InteractionOperations InterOp;
    EXPECT_EQ(InterOp.GetMessage().x_coord(), 0);
    EXPECT_EQ(InterOp.GetMessage().y_coord(), 0);
}

TEST(MESSAGE_TEST, send_receive_test) {
    std::string file_path = "../../data/buttons_coords.bin";
    keyboard_mouse::buttons_coords message;
    message.add_button_pressed(true);
    message.add_button_pressed(false);
    message.add_button_pressed(false);
    message.set_x_coord(5);
    message.set_y_coord(10);

    SendInteraction SendM(file_path, message);
    SendM.PrintMessage();

    if (SendM.SendIt()) cout<<"Error with sending";

    keyboard_mouse::buttons_coords ReceiveMessage;
    ReceiveInteraction ReceiveM(file_path, ReceiveMessage);
    ifstream inp;
    keyboard_mouse::buttons_coords parsed_buttons_coords;
    if(ReceiveM.ReceiveIt()) cout<<"Error wint receiving";
    ReceiveM.PrintMessage();
    int i = 0;
    for(const bool &button :SendM.GetMessage().button_pressed()){
        EXPECT_EQ(button, ReceiveM.GetMessage().button_pressed()[i]);
    };
    EXPECT_EQ(SendM.GetMessage().x_coord(), ReceiveM.GetMessage().x_coord());
    EXPECT_EQ(SendM.GetMessage().y_coord(), ReceiveM.GetMessage().y_coord());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}