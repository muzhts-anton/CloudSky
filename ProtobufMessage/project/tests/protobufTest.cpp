#include <gtest/gtest.h>

#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"

#include <bits/stdc++.h>
#include <fstream>
#include <iostream>

TEST(MESSAGE_TEST, constructorMessageTest)
{
    KeyboardMouse::ButtonsCoords message;
    std::string filePath = "buttonsCoords.bin";
    bool buttonSeq[buttonQuanity] { true, false, false };
    for (int i = 0; i < 3; ++i) {
        message.add_buttonpressed(buttonSeq[i]);
    }
    int coords[coordQuanity] { 2, 45 };
    message.set_xcoord(coords[0]);
    message.set_ycoord(coords[1]);
    ViktorDev::InteractionOperations interOp(message, filePath);
    int i = 0;
    for (const bool& button : interOp.getMessage().buttonpressed()) {
        EXPECT_EQ(buttonSeq[i], button);
        ++i;
    };
    std::cout << "interOp.getMessage().xcoord() = " << interOp.getMessage().xcoord() << std::endl;
    std::cout << "interOp.getMessage().ycoord() = " << interOp.getMessage().ycoord() << std::endl;
    std::cout << "coords[0] = " << coords[0] << std::endl;
    std::cout << "coords[1] = " << coords[1] << std::endl;
    EXPECT_EQ(interOp.getMessage().xcoord(), coords[0]);
    EXPECT_EQ(interOp.getMessage().ycoord(), coords[1]);
}

TEST(MESSAGE_TEST, constructorCoordsTest)
{
    bool buttonSeq[buttonQuanity] { true, false, false };
    int coords[coordQuanity] { 2, 45 };
    std::string filePath = "buttonsCoords.bin";
    ViktorDev::InteractionOperations interOp(buttonSeq, coords, filePath);
    int i = 0;
    for (const bool& button : interOp.getMessage().buttonpressed()) {
        EXPECT_EQ(buttonSeq[i], button);
        ++i;
    };
    EXPECT_EQ(interOp.getMessage().xcoord(), coords[0]);
    EXPECT_EQ(interOp.getMessage().ycoord(), coords[1]);
}

TEST(MESSAGE_TEST, defaultConstructorTest)
{
    ViktorDev::InteractionOperations interOp;
    EXPECT_EQ(interOp.getMessage().xcoord(), 0);
    EXPECT_EQ(interOp.getMessage().ycoord(), 0);
}

TEST(MESSAGE_TEST, sendReceiveTest)
{
    const int number = 20;
    std::string filePath = "ButtonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;
    std::vector<bool> vecKb(number);
    std::vector<bool> vecMouse(number);
    std::fill(vecKb.begin(), vecKb.end(), true);
    std::fill(vecMouse.begin(), vecMouse.end(), true);
    fill(vecMouse.begin(), vecMouse.end(), false);
    for (auto it = vecKb.begin(), itM = vecMouse.begin(); it != vecKb.end() || itM != vecMouse.end(); ++it, ++itM) {
        message.add_buttonpressed(*it);
        message.add_mousebuttons(*itM);
    }
    message.set_xcoord(5);
    message.set_ycoord(10);

    ViktorDev::SendInteraction sendMessageHandler(filePath, message);
    sendMessageHandler.printMessage();

    if (sendMessageHandler.sendIt())
        std::cout << "Error with sending";

    KeyboardMouse::ButtonsCoords receiveMessageHandler;
    ViktorDev::ReceiveInteraction receiveMessangeHandler(filePath, receiveMessageHandler);
    std::ifstream inp;
    KeyboardMouse::ButtonsCoords parsed_ButtonsCoords;
    if (receiveMessangeHandler.receiveIt())
        std::cout << "Error wint receiving";
    receiveMessangeHandler.printMessage();
    int i = 0;
    for (const bool& button : sendMessageHandler.getMessage().buttonpressed()) {
        EXPECT_EQ(button, receiveMessangeHandler.getMessage().buttonpressed()[i]);
        ++i;
    };
    i = 0;
    for (const bool& mouseButton : sendMessageHandler.getMessage().mousebuttons()) {
        EXPECT_EQ(mouseButton, receiveMessangeHandler.getMessage().mousebuttons()[i]);
        ++i;
    };

    EXPECT_EQ(sendMessageHandler.getMessage().xcoord(), receiveMessangeHandler.getMessage().xcoord());
    EXPECT_EQ(sendMessageHandler.getMessage().ycoord(), receiveMessangeHandler.getMessage().ycoord());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}