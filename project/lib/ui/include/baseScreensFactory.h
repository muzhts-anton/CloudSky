#ifndef BASESCREENSFACTORY_H
#define BASESCREENSFACTORY_H

#include "baseFragment.h"
#include "screenNames.h"

class BaseScreensFactory
{
public:
    virtual fragment::BaseFragment *create(screens::ScreenNames tag) = 0;
    virtual screens::ScreenNames getStart() = 0;
};

#endif // BASESCREENSFACTORY_H