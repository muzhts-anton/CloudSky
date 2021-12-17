#include "screensFactory.h"
#include "addGameFragment.h"
#include "authFragment.h"
#include "baseFragment.h"
#include "gameFragment.h"
#include "mainFragment.h"
#include "openGameFragment.h"
#include "regFragment.h"
#include "startFragment.h"

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
    case screens::ScreenNames::ADDGAME:
        return new fragment::AddGameFragment;
    case screens::ScreenNames::OPENGAME:
        return new fragment::OpenGameFragment;
    default:
        return nullptr;
    }
}

screens::ScreenNames ScreensFactory::getStart()
{
    return screens::ScreenNames::START;
}