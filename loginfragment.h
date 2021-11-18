#ifndef LOGINFRAGMENT_H
#define LOGINFRAGMENT_H

#include "basefragment.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>


class LoginFragment : public BaseFragment
{
    Q_OBJECT
public:
    LoginFragment();

private:
    void checkData();
    void sendToDB();

private:
    QCheckBox *rememberMeCheckbox;
    QLineEdit *loginTextbox;
    QLineEdit *passwordTextbox;
    QPushButton *loginButton;
};

#endif // LOGINFRAGMENT_H
