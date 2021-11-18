#include "gtest/gtest.h"

#include "settingsfragment.h"
#include "loginfragment.h"
#include "registerfragment.h"

TEST(settingsTest, volume) {
    SettingsFragment tmp;
    tmp->valueChanged(50);
    // open a settings json and check the value
}

TEST(loginTest, volume) {
    LoginFragment tmp;
    tmp->checkData(/* Data */);
    // check
}

TEST(loginTest, volume) {
    RegisterFragment tmp;
    tmp->checkData(/* Data */);
    // check
}
