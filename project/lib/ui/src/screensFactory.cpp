#include "screensFactory.h"
#include "baseFragment.h"
#include "mainFragment.h"
#include "gameFragment.h"
#include "startFragment.h"
#include "authFragment.h"
#include "regFragment.h"

fragment::BaseFragment* ScreensFactory::create(screens::ScreenNames tag)
{
    switch (tag) {
    case screens::ScreenNames::GAME:
        return new fragment::GameFragment;
    case screens::ScreenNames::START:
        return new fragment::StartFragment;
    case screens::ScreenNames::MAIN:
        return new fragment::MainFragment;
    case screens::ScreenNames::LOGIN:
        return new fragment::AuthFragment;
    case screens::ScreenNames::REGISTER:
        return new fragment::RegFragment;
    default:
        return nullptr;
    }
}

screens::ScreenNames ScreensFactory::getStart()
{
    return screens::ScreenNames::START;
}