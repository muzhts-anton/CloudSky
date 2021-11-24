#include <gtest/gtest.h>

#include "../include/MessageOperations.h"

TEST(MESSAGE_TEST, constructorMessageTest)
{
    KeyboardMouse::ButtonsCoords message;
    bool buttonSeq[BUTTON_QUANITY] { true, false, false };
    for (int i = 0; i < 3; ++i) {
        message.add_buttonpressed(buttonSeq[i]);
    }
    int coords[COORD_QUANITY] { 2, 45 };
    for (int i = 0; i < 2; ++i) {
        message.set_xcoord(coords[i]);
    }
    InteractionOperations interOp(message);
    int i = 0;
    for (const bool& button : interOp.getMessage().buttonPressed()) {
        EXPECT_EQ(buttonSeq[i], button);
        ++i;
    };
    EXPECT_EQ(interOp.getMessage().xCoord(), coords[0]);
    EXPECT_EQ(interOp.getMessage().yCoord(), coords[1]);
}

TEST(MESSAGE_TEST, constructorCoordsTest)
{
    bool buttonSeq[BUTTON_QUANITY] { true, false, false };
    int coords[COORD_QUANITY] { 2, 45 };
    InteractionOperations interOp(buttonSeq, coords);
    int i = 0;
    for (const bool& button : interOp.getMessage().buttonPressed()) {
        EXPECT_EQ(buttonSeq[i], button);
        ++i;
    };
    EXPECT_EQ(interOp.getMessage().xCoord(), coords[0]);
    EXPECT_EQ(interOp.getMessage().yCoord(), coords[1]);
}

TEST(MESSAGE_TEST, defaultConstructorTest)
{
    InteractionOperations interOp;
    EXPECT_EQ(interOp.getMessage().xCoord(), 0);
    EXPECT_EQ(interOp.getMessage().yCoord(), 0);
}

TEST(MESSAGE_TEST, sendReceiveTest)
{
    std::string filePath = "ButtonsCoords.bin";
    KeyboardMouse::ButtonsCoords message;
    message.add_buttonpressed(true);
    message.add_buttonpressed(false);
    message.add_buttonpressed(false);
    message.set_xcoord(5);
    message.set_ycoord(10);

    SendInteraction sendMessageHandler(filePath, message);
    sendMessageHandler.printMessage();

    if (sendMessageHandler.sendIt())
        cout << "Error with sending";

    KeyboardMouse::ButtonsCoords receiveMessageHandler;
    ReceiveInteraction receiveMessangeHandler(filePath, receiveMessageHandler);
    ifstream inp;
    KeyboardMouse::ButtonsCoords parsed_ButtonsCoords;
    if (receiveMessangeHandler.receiveIt())
        cout << "Error wint receiving";
    receiveMessangeHandler.printMessage();
    int i = 0;
    for (const bool& button : sendMessageHandler.getMessage().buttonPressed()) {
        EXPECT_EQ(button, receiveMessangeHandler.getMessage().buttonPressed()[i]);
    };
    EXPECT_EQ(sendMessageHandler.getMessage().xCoord(), receiveMessangeHandler.getMessage().xCoord());
    EXPECT_EQ(sendMessageHandler.getMessage().yCoord(), receiveMessangeHandler.getMessage().yCoord());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}