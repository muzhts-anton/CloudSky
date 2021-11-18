#ifndef BASESCREENFACTORY_H
#define BASESCREENFACTORY_H

#include "basefragment.h"

#include <QString>


class BaseScreenFactory
{
public:
    BaseScreenFactory();
    virtual BaseFragment* create(QString tag);
    virtual QString createStart();
};

#endif // BASESCREENFACTORY_H
