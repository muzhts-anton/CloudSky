#ifndef SCREENFACTORY_H
#define SCREENFACTORY_H

#include "basescreenfactory.h"


class ScreenFactory : public BaseScreenFactory
{
public:
    ScreenFactory();
    BaseFragment* create(QString tag) override;
    QString createStart() override;
};

#endif // SCREENFACTORY_H
