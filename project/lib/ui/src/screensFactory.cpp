#include "screensFactory.h"
#include "baseFragment.h"

fragment::BaseFragment* ScreensFactory::create(screens::ScreenNames tag)
{
    switch (tag) {
    case screens::ScreenNames::START:
        // return new StartFragment;

    default:
        return nullptr;
    }
}

screens::ScreenNames ScreensFactory::getStart()
{
    return screens::ScreenNames::START;
}