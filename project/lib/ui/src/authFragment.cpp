#include "authFragment.h"

#include <QVBoxLayout>

namespace fragment {

AuthFragment::AuthFragment()
    : _userName(new QLineEdit(this))
    , _userPassword(new QLineEdit(this))
    , _authBut(new QPushButton("Authorization"))
{
    _userName->setStyleSheet("QLineEdit { background-color: rgb(154,154,154); color: white; } QLineEdit:active { border: none; border-radius: 7px; padding: 10px; color: white; }");
    _userPassword->setStyleSheet("QLineEdit { background-color: rgb(154,154,154); color: white; } QLineEdit:active { border: none; border-radius: 7px; padding: 10px; color: white; }");
    _authBut->setStyleSheet("background-color: rgb(189,144,255); border: none; border-radius: 7px; padding: 10px; color: white;");

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
