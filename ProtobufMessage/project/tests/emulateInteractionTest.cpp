#include <gtest/gtest.h>

#include "../include/messageOperations.h"
#include "../include/operationEmulation.h"

using namespace std;

TEST(EMULATE_TEST, coordsTest)
{
    string filePath = "";
    bool buttonSeq[buttonQuanity] { true, false, false };
    int coords[coordQuanity] { 2, 45 };
    EmulateInteraction emulate(filePath, buttonSeq, coords);
    int coordX = emulate.getCurrentXCoord();
    int coordY = emulate.getCurrentYCoord();
    emulate.emulateInteraction(buttonSeq, coords[0], coords[1]);
    EXPECT_EQ(coordX, emulate.getCurrentXCoord());
    EXPECT_EQ(coordY, emulate.getCurrentYCoord());
}

TEST(EMULATE_TEST, buttonTest)
{
    string filePath = "";
    bool buttonSeq[buttonQuanity] { true, false, false };
     int coords[coordQuanity] { 100, 886 };
    EmulateInteraction emulate(filePath, buttonSeq, coords);

    EXPECT_EQ(true, emulate.getCurrentButtonState('a'));
    EXPECT_EQ(true, emulate.getCurrentButtonState('b'));
    EXPECT_EQ(true, emulate.getCurrentButtonState('c'));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}