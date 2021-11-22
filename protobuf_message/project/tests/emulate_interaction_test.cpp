#include <gtest/gtest.h>


#include "../include/emulate_operations.h"
#include "../include/message_operations.h"

using namespace std;

TEST(EMULATE_TEST, coords_test) {
    string file_path = "";
    bool ButtonSeq[button_quanity]{true,false,false};
    int coords[coord_quanity]{2, 45};
    EmulateInteraction emulate(file_path, ButtonSeq, coords);
    int coord_x = emulate.get_current_x_coord();
    int coord_y = emulate.get_current_y_coord();
    emulate.emulate_interaction(ButtonSeq, coords[0], coords[1]);
    EXPECT_EQ(coord_x, emulate.get_current_x_coord());
    EXPECT_EQ(coord_y, emulate.get_current_y_coord());
}

TEST(EMULATE_TEST, button_test) {
    string file_path = "";
    bool ButtonSeq[button_quanity]{true,false,false}; 
    int coords[coord_quanity]{100, 886};
    EmulateInteraction emulate(file_path, ButtonSeq, coords);

    EXPECT_EQ(true, emulate.get_current_button_state('a'));
    EXPECT_EQ(true, emulate.get_current_button_state('b'));
    EXPECT_EQ(true, emulate.get_current_button_state('c'));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}