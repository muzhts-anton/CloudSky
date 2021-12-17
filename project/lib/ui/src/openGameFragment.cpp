#include "openGameFragment.h"
#include "fragmentThemeStyle.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

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
    _gameSelecterBox->addItem("CS:GO");
    _gameSelecterBox->addItem("Horizon: Zero Dawn");

    QHBoxLayout* buttsHL = new QHBoxLayout;
    buttsHL->addWidget(_backBut);
    buttsHL->addWidget(_openBut);

    QVBoxLayout* mainVL = new QVBoxLayout(this);
    mainVL->addWidget(_explanationLabel);
    mainVL->addWidget(_gameSelecterBox);
    mainVL->addLayout(buttsHL);

    connect(_openBut, &QPushButton::clicked, this, &OpenGameFragment::onOpen);
    connect(_backBut, &QPushButton::clicked, this, &OpenGameFragment::onBack);
}

OpenGameFragment::~OpenGameFragment()
{
    delete _explanationLabel;
    delete _gameSelecterBox;
    delete _openBut;
    delete _backBut;
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
