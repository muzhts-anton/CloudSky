#include "mainFragment.h"
#include "fragmentThemeStyle.h"

#include <QDebug>
#include <QDir>
#include <QPixmap>

namespace fragment {

MainFragment::MainFragment()
    : _greetingLabel(new QLabel("Hi []! This is [] coins on your account."))
    , _pic(new QLabel(this))
    , _watcher(new secondfit::ButtonHoverWatcher(this))
    , _openGameBut(new QPushButton("Go to game screen"))
    , _settingsBut(new QPushButton("Settings [open soon]"))
    , _addGameBut(new QPushButton("Add Game"))
    , _logOutBut(new QPushButton("Log Out"))
{
    _greetingLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _openGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _settingsBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _addGameBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _logOutBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));


    QDir logofile;
    logofile.cdUp();
    logofile.cd("lib/ui/media/");

    _pic->setPixmap(QPixmap(logofile.absoluteFilePath("logout.png")));
    _pic->setScaledContents(true);
    _pic->setFixedHeight(235);
    _pic->setFixedWidth(235);

    _mainHL = new QHBoxLayout(this);
    _buttonsVL = new QVBoxLayout;

    _buttonsVL->addWidget(_greetingLabel);
    _buttonsVL->addWidget(_openGameBut);
    _buttonsVL->addWidget(_settingsBut);
    _buttonsVL->addWidget(_addGameBut);
    _buttonsVL->addWidget(_logOutBut);

    _mainHL->addLayout(_buttonsVL);
    _mainHL->addWidget(_pic);
    
    _buttonsVL->setAlignment(Qt::AlignCenter);
    _mainHL->setAlignment(Qt::AlignCenter);

    _openGameBut->installEventFilter(_watcher);
    _addGameBut->installEventFilter(_watcher);
    _settingsBut->installEventFilter(_watcher);
    _logOutBut->installEventFilter(_watcher);

    connect(_watcher, &secondfit::ButtonHoverWatcher::onButHovered, this, &MainFragment::onButHovered);
    connect(_openGameBut, &QPushButton::clicked, this, &MainFragment::onGame);
    connect(_addGameBut, &QPushButton::clicked, this, &MainFragment::onAddGame);
    connect(_logOutBut, &QPushButton::clicked, this, &MainFragment::onLogOut);
}

// slots
void MainFragment::onGame()
{
    emit navigateTo(screens::ScreenNames::OPENGAME);
}

void MainFragment::onAddGame()
{
    emit navigateTo(screens::ScreenNames::ADDGAME);
}

void MainFragment::onButHovered(QPushButton* obj)
{
    QDir logofile;
    logofile.cdUp();
    logofile.cd("lib/ui/media/");

    if (obj == _settingsBut)
        _pic->setPixmap(QPixmap(logofile.absoluteFilePath("settings.png")));
    else if (obj == _openGameBut)
        _pic->setPixmap(QPixmap(logofile.absoluteFilePath("controller.png")));
    else if (obj == _logOutBut)
        _pic->setPixmap(QPixmap(logofile.absoluteFilePath("logout.png")));
    else if (obj == _addGameBut)
        _pic->setPixmap(QPixmap(logofile.absoluteFilePath("sale.png")));

}

void MainFragment::onLogOut()
{
    emit back();
}

} // namespace fragment
