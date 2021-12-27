#include <gtest/gtest.h>

#include "messageOperations.h"
#include "operationEmulation.h"

TEST(EMULATE_TEST, coordsTest)
{
    KeyboardMouse::ButtonsCoords message;
    bool pressedButton[buttonQuanity] { false, false, true, true, false, false, false, false, false };
    for (int i = 0; i < buttonQuanity; ++i) {
        message.add_buttonpressed(pressedButton[i]);
    };
    message.set_xcoord(-50);
    message.set_ycoord(-100);
    message.add_mousebuttons(false);
    message.add_mousebuttons(true);
    ViktorDev::EmulationMouse mouseEmulation;
    mouseEmulation.setCoordsButtons(message);
    int coordX = mouseEmulation.getCurrentXCoord();
    int coordY = mouseEmulation.getCurrentYCoord();
    mouseEmulation.emulateMouse();
    EXPECT_EQ(coordX, mouseEmulation.getCurrentXCoord());
    EXPECT_EQ(coordY, mouseEmulation.getCurrentYCoord());
}

TEST(EMULATE_TEST, buttonTest)
{
    KeyboardMouse::ButtonsCoords message;
    bool pressedButton[buttonQuanity] { true, true, true, true, true, true, true, true, true };
    for (int i = 0; i < buttonQuanity; ++i) {
        message.add_buttonpressed(pressedButton[i]);
    };

    message.set_xcoord(-50);
    message.set_ycoord(-100);
    message.add_mousebuttons(false);
    message.add_mousebuttons(true);

    ViktorDev::EmelationKeyBoard kbEmulation;
    kbEmulation.setKeyboard(message);
    kbEmulation.emulateKeyboard();

    ViktorDev::EmulationMouse mouseEmulation;
    mouseEmulation.setCoordsButtons(message);
    mouseEmulation.emulateMouse();

    EXPECT_EQ(true, kbEmulation.getCurrentButtonState(KEY_W));
    EXPECT_EQ(true, kbEmulation.getCurrentButtonState(KEY_A));
    EXPECT_EQ(true, kbEmulation.getCurrentButtonState(KEY_S));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}