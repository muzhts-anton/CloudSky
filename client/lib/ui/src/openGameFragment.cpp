#include "openGameFragment.h"
#include "fragmentThemeStyle.h"

namespace fragment {

OpenGameFragment::OpenGameFragment()
    : _explanationLabel(new QLabel("Select the game u want to play:"))
    , _gameSelecterBox(new QComboBox)
    , _openBut(new QPushButton("Open selected game"))
    , _backBut(new QPushButton("Back"))
{
    _explanationLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _openBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _backBut->setFixedWidth(75);
    _gameSelecterBox->addItem("Forza Horizon 6");
    _gameSelecterBox->addItem("Horizon: Zero Dawn");

    _buttsHL = new QHBoxLayout;
    _buttsHL->addWidget(_backBut);
    _buttsHL->addWidget(_openBut);

    _mainVL = new QVBoxLayout(this);
    _mainVL->addWidget(_explanationLabel);
    _mainVL->addWidget(_gameSelecterBox);
    _mainVL->addLayout(_buttsHL);

    connect(_openBut, &QPushButton::clicked, this, &OpenGameFragment::onOpen);
    connect(_backBut, &QPushButton::clicked, this, &OpenGameFragment::onBack);
}

void OpenGameFragment::onResume()
{
    emit back();
}

// slots
void OpenGameFragment::onOpen()
{
    emit navigateTo(screens::ScreenNames::GAME);
}

void OpenGameFragment::onBack()
{
    emit back();
}

} // namespace fragment
