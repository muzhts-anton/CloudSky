#include "authFragment.h"
#include "fragmentThemeStyle.h"

#include <QVBoxLayout>

namespace fragment {

AuthFragment::AuthFragment()
    : _userName(new QLineEdit(this))
    , _userPassword(new QLineEdit(this))
    , _authBut(new QPushButton("Authorization"))
{
    _userName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _authBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::BUTTON));

    _userName->setPlaceholderText("User Name");
    _userPassword->setPlaceholderText("Password");
    _userPassword->setEchoMode(QLineEdit::Password);

    QVBoxLayout* mainVL = new QVBoxLayout(this);
    mainVL->addWidget(_userName);
    mainVL->addWidget(_userPassword);
    mainVL->addWidget(_authBut);

    mainVL->setAlignment(Qt::AlignCenter);

    connect(_authBut, &QPushButton::clicked, this, &AuthFragment::onAuth);
}

AuthFragment::~AuthFragment()
{
    delete _userName;
    delete _userPassword;
    delete _authBut;
}

bool AuthFragment::checkData(QString username, QString password)
{
    (void)username;
    (void)password;
    // TODO(Tony, Viktor): implement with DB
    return true;
}

// slots
void AuthFragment::onAuth()
{
    if(this->checkData(_userName->text(), _userPassword->text()))
        emit navigateTo(screens::ScreenNames::MAIN);
}

} // namespace fragment
