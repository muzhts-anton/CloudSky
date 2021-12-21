#include "regFragment.h"
#include "fragmentThemeStyle.h"

#include <QtGui>

namespace fragment {

RegFragment::RegFragment()
    : _explanLabel(new QLabel("Input your data to confirm registration"))
    , _userFirstName(new QLineEdit)
    , _userSecondName(new QLineEdit)
    , _userCountry(new QLineEdit)
    , _userEmail(new QLineEdit)
    , _userNickName(new QLineEdit)
    , _userFirstPassword(new QLineEdit)
    , _userSecondPassword(new QLineEdit)
    , _ageTxt(new QLabel("Enter your age"))
    , _userAge(new QSpinBox)
    , _errorLabel(new QLabel("<i>To check and send the data push the button</i>"))
    , _regBut(new QPushButton("Confirm registration"))
    , _backBut(new QPushButton("Back"))
{
    _userFirstName->setPlaceholderText("First Name");
    _userSecondName->setPlaceholderText("Second Name");
    _userCountry->setPlaceholderText("Country");
    _userEmail->setPlaceholderText("Email address");
    _userNickName->setPlaceholderText("Your registration nickname");
    _userFirstPassword->setPlaceholderText("Password");
    _userSecondPassword->setPlaceholderText("Re-enter password to confirm");

    _userFirstPassword->setEchoMode(QLineEdit::Password);
    _userSecondPassword->setEchoMode(QLineEdit::Password);
    _userAge->setButtonSymbols(QAbstractSpinBox::NoButtons);
    _userAge->setFixedWidth(100);
    _backBut->setFixedWidth(75);

    _explanLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _userFirstName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userSecondName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userCountry->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userEmail->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userNickName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userFirstPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userSecondPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _ageTxt->setStyleSheet(themestyle::fixed.value(themestyle::Type::LOWERLABEL));
    _userAge->setStyleSheet(themestyle::fixed.value(themestyle::Type::SPINBOX) + themestyle::active.value(themestyle::Type::SPINBOX));
    _errorLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::LOWERLABEL));
    _regBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _ageHL = new QHBoxLayout;
    _ageHL->addWidget(_userAge);
    _ageHL->addWidget(_ageTxt);

    _buttsHL = new QHBoxLayout;
    _buttsHL->addWidget(_backBut);
    _buttsHL->addWidget(_regBut);

    _mainVL = new QVBoxLayout(this);
    _mainVL->addWidget(_explanLabel);
    _mainVL->addWidget(_userFirstName);
    _mainVL->addWidget(_userSecondName);
    _mainVL->addWidget(_userCountry);
    _mainVL->addWidget(_userEmail);
    _mainVL->addWidget(_userNickName);
    _mainVL->addWidget(_userFirstPassword);
    _mainVL->addWidget(_userSecondPassword);
    _mainVL->addLayout(_ageHL);
    _mainVL->addWidget(_errorLabel);
    _mainVL->addLayout(_buttsHL);

    connect(_regBut, &QPushButton::clicked, this, &RegFragment::onReg);
    connect(_backBut, &QPushButton::clicked, this, &RegFragment::onBack);
}

bool RegFragment::checkData()
{
    if (_userFirstPassword->text() != _userSecondPassword->text()) {
        _errorLabel->setText("Passwords are different");
        _errorLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::ATTENTIONLABEL));
        return false;
    }
    return true;
}

void RegFragment::onResume()
{
    emit back();
}

// slots
void RegFragment::onReg()
{
    if (this->checkData())
        emit navigateTo(screens::ScreenNames::MAIN);
}

void RegFragment::onBack()
{
    emit back();
}

} // namespace fragment