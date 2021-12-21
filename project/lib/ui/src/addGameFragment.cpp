#include "addGameFragment.h"
#include "fragmentThemeStyle.h"

#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

namespace fragment {

AddGameFragment::AddGameFragment()
    : _cashBalance(new QLabel("Your cash balance: []"))
    , _picFirst(new QLabel)
    , _picSecond(new QLabel)
    , _descripFirst(new QLabel("So nice game, u know"))
    , _descripSecond(new QLabel("OMG it's so beautiful"))
    , _addFirstGameBut(new QPushButton("Buy this first game"))
    , _addSecondGameBut(new QPushButton("Buy this second game"))
    , _backBut(new QPushButton("Quit"))
{
    _cashBalance->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _descripFirst->setStyleSheet(themestyle::fixed.value(themestyle::Type::LOWERLABEL));
    _descripSecond->setStyleSheet(themestyle::fixed.value(themestyle::Type::LOWERLABEL));
    _addFirstGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _addSecondGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _backBut->setFixedWidth(75);

    _picFirst->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("csgo.jpg")));
    _picFirst->setFixedHeight(200);
    _picFirst->setFixedWidth(200);
    _picSecond->setPixmap(QPixmap(QDir("project/lib/ui/media/").absoluteFilePath("horizon.png")));
    _picSecond->setFixedHeight(200);
    _picSecond->setFixedWidth(200);

    _firstgameVL = new QVBoxLayout;
    _firstgameVL->addWidget(_picFirst);
    _firstgameVL->addWidget(_descripFirst);
    _firstgameVL->addWidget(_addFirstGameBut);

    _secondgameVL = new QVBoxLayout;
    _secondgameVL->addWidget(_picSecond);
    _secondgameVL->addWidget(_descripSecond);
    _secondgameVL->addWidget(_addSecondGameBut);

    _gamesHL = new QHBoxLayout;
    _gamesHL->addLayout(_firstgameVL);
    _gamesHL->addLayout(_secondgameVL);

    _topBarHL = new QHBoxLayout;
    _topBarHL->addWidget(_cashBalance);
    _topBarHL->addWidget(_backBut);

    _mainVL = new QVBoxLayout(this);
    _mainVL->addLayout(_topBarHL);
    _mainVL->addLayout(_gamesHL);

    connect(_addFirstGameBut, &QPushButton::clicked, this, &AddGameFragment::onAddFirst);
    connect(_addSecondGameBut, &QPushButton::clicked, this, &AddGameFragment::onAddSecond);
    connect(_backBut, &QPushButton::clicked, this, &AddGameFragment::onBack);
}

void AddGameFragment::onAddFirst()
{
    _addFirstGameBut->setText("nice");
}

void AddGameFragment::onAddSecond()
{
    _addSecondGameBut->setText("well done");
}

void AddGameFragment::onBack()
{
    emit back();
}

} // namespace fragment