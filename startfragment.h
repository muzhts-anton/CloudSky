#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "basefragment.h"

#include <QPushButton>


class StartFragment : public BaseFragment
{
    Q_OBJECT
public:
    StartFragment();

private slots:
    void GoToLoginButtonPressed();
    void GoToRegisterButtonPressed();

private:
    QPushButton *LoginButton;
    QPushButton *RegButton;
};

#endif // STARTFRAGMENT_H
