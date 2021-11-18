#ifndef REGISTERFRAGMENT_H
#define REGISTERFRAGMENT_H

#include "basefragment.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>


class RegisterFragment : public BaseFragment
{
public:
    RegisterFragment();

private:
    void sceckData();
    void sendToDB();

private:
    QCheckBox *rememberMeCheckbox;
    QLineEdit *regTextbox;
    QLineEdit *passwordTextbox;
    QPushButton *regButton;
};

#endif // REGISTERFRAGMENT_H
