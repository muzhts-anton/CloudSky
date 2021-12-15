#include "authFragment.h"
#include "fragmentThemeStyle.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

namespace fragment {

AuthFragment::AuthFragment()
    : _explanLabel(new QLabel("Input your data to confirm authorization"))
    , _userName(new QLineEdit(this))
    , _userPassword(new QLineEdit(this))
    , _authBut(new QPushButton("Authorization"))
    , _backBut(new QPushButton("Back"))
{
    _explanLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _userName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _authBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _userName->setPlaceholderText("User Name");
    _userPassword->setPlaceholderText("Password");
    _userPassword->setEchoMode(QLineEdit::Password);
    _backBut->setFixedWidth(75);

    QHBoxLayout* buttsHL = new QHBoxLayout;
    buttsHL->addWidget(_backBut);
    buttsHL->addWidget(_authBut);

    QVBoxLayout* mainVL = new QVBoxLayout(this);
    mainVL->addWidget(_explanLabel);
    mainVL->addWidget(_userName);
    mainVL->addWidget(_userPassword);
    mainVL->addLayout(buttsHL);

    mainVL->setAlignment(Qt::AlignCenter);

    connect(_authBut, &QPushButton::clicked, this, &AuthFragment::onAuth);
    connect(_backBut, &QPushButton::clicked, this, &AuthFragment::onBack);
}

AuthFragment::~AuthFragment()
{
    delete _userName;
    delete _userPassword;
    delete _authBut;
    delete _backBut;
    delete _explanLabel;
}

bool AuthFragment::checkData()
{
    // TODO(Tony, Viktor): implement with DB
    return true;
}

void AuthFragment::onResume()
{
    emit back();
}

// slots
void AuthFragment::onAuth()
{
    if(this->checkData())
        emit navigateTo(screens::ScreenNames::MAIN);
}

void AuthFragment::onBack()
{
    emit back();
}

} // namespace fragment
