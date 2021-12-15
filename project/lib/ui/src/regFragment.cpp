#include "regFragment.h"
#include "fragmentThemeStyle.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace fragment {

RegFragment::RegFragment()
    : _userFirstName(new QLineEdit)
    , _userSecondName(new QLineEdit)
    , _userNickName(new QLineEdit)
    , _userFirstPassword(new QLineEdit)
    , _userSecondPassword(new QLineEdit)
    , _ageTxt(new QLabel("Enter your age"))
    , _userAge(new QSpinBox)
    , _regBut(new QPushButton("Confirm registration"))
{
    _userFirstName->setPlaceholderText("First Name");
    _userSecondName->setPlaceholderText("Second Name");
    _userNickName->setPlaceholderText("Your registration nickname");
    _userFirstPassword->setPlaceholderText("Password");
    _userSecondPassword->setPlaceholderText("Re-enter password to confirm");

    _userFirstPassword->setEchoMode(QLineEdit::Password);
    _userSecondPassword->setEchoMode(QLineEdit::Password);
    _userAge->setButtonSymbols(QAbstractSpinBox::NoButtons);

    _userFirstName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userSecondName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userNickName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userFirstPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userSecondPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _ageTxt->setStyleSheet(themestyle::fixed.value(themestyle::Type::LABEL));
    _userAge->setStyleSheet(themestyle::fixed.value(themestyle::Type::SPINBOX) + themestyle::active.value(themestyle::Type::SPINBOX));
    _regBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::BUTTON));

    QHBoxLayout* ageHL = new QHBoxLayout;
    ageHL->addWidget(_userAge);
    ageHL->addWidget(_ageTxt);

    QVBoxLayout* mainVL = new QVBoxLayout(this);
    mainVL->addWidget(_userFirstName);
    mainVL->addWidget(_userSecondName);
    mainVL->addWidget(_userNickName);
    mainVL->addWidget(_userFirstPassword);
    mainVL->addWidget(_userSecondPassword);
    mainVL->addLayout(ageHL);
    mainVL->addWidget(_regBut);

    connect(_regBut, &QPushButton::clicked, this, &RegFragment::onReg);
}

RegFragment::~RegFragment()
{
    delete _userFirstName;
    delete _userSecondName;
    delete _userNickName;
    delete _userFirstPassword;
    delete _userSecondPassword;
    delete _ageTxt;
    delete _userAge;
    delete _regBut;
}

// slots
void RegFragment::onReg()
{
    emit navigateTo(screens::ScreenNames::MAIN);
}

} // namespace fragment