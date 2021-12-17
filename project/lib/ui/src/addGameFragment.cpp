#include "addGameFragment.h"
#include "fragmentThemeStyle.h"

#include <QDir>
#include <QHBoxLayout>
#include <QPixmap>
#include <QVBoxLayout>

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

    QVBoxLayout* firstgameVL = new QVBoxLayout;
    firstgameVL->addWidget(_picFirst);
    firstgameVL->addWidget(_descripFirst);
    firstgameVL->addWidget(_addFirstGameBut);

    QVBoxLayout* secondgameVL = new QVBoxLayout;
    secondgameVL->addWidget(_picSecond);
    secondgameVL->addWidget(_descripSecond);
    secondgameVL->addWidget(_addSecondGameBut);

    QHBoxLayout* gamesHL = new QHBoxLayout;
    gamesHL->addLayout(firstgameVL);
    gamesHL->addLayout(secondgameVL);

    QHBoxLayout* topBarHL = new QHBoxLayout;
    topBarHL->addWidget(_cashBalance);
    topBarHL->addWidget(_backBut);

    QVBoxLayout* mainVL = new QVBoxLayout(this);
    mainVL->addLayout(topBarHL);
    mainVL->addLayout(gamesHL);

    connect(_addFirstGameBut, &QPushButton::clicked, this, &AddGameFragment::onAddFirst);
    connect(_addSecondGameBut, &QPushButton::clicked, this, &AddGameFragment::onAddSecond);
    connect(_backBut, &QPushButton::clicked, this, &AddGameFragment::onBack);
}

AddGameFragment::~AddGameFragment()
{
    delete _cashBalance;
    delete _picFirst;
    delete _picSecond;
    delete _descripFirst;
    delete _descripSecond;
    delete _addFirstGameBut;
    delete _addSecondGameBut;
    delete _backBut;
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