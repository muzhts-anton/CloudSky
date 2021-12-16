#include "screensFactory.h"
#include "baseFragment.h"
#include "gameFragment.h"
#include "startFragment.h"

fragment::BaseFragment* ScreensFactory::create(screens::ScreenNames tag)
{
    switch (tag) {
    case screens::ScreenNames::GAME: return new fragment::GameFragment;
    case screens::ScreenNames::START: return new fragment::StartFragment;
    default: return nullptr;
    }
}

screens::ScreenNames ScreensFactory::getStart()
{
    return screens::ScreenNames::START;
}