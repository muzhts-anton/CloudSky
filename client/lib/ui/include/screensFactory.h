#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include "baseScreensFactory.h"
#include "screenNames.h"

class ScreensFactory : public BaseScreensFactory
{
public:
    ScreensFactory() = default;
    ~ScreensFactory() = default;

    fragment::BaseFragment *create(screens::ScreenNames tag) override;
    screens::ScreenNames getStart() override;
};

#endif // SCREENSFACTORY_H