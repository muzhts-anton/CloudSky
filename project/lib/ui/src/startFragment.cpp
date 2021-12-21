#include "startFragment.h"
#include "fragmentThemeStyle.h"

#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QPixmap>

namespace fragment {

StartFragment::StartFragment()
    : _authBut(new QPushButton("Authorization"))
    , _regBut(new QPushButton("Registration"))
{
    _authBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _regBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));

    QDir logofile;
    logofile.cd("project/lib/ui/media/");

    QLabel* logo = new QLabel(this);
    QPixmap piclogo(logofile.absoluteFilePath("CloudSky.png"));
    logo->setPixmap(piclogo);
    logo->setScaledContents(true);
    logo->setFixedHeight(235);
    logo->setFixedWidth(235);

    _mainHL = new QHBoxLayout(this);
    _buttonsVL = new QVBoxLayout;
    _mainHL->addWidget(logo);
    _mainHL->addLayout(_buttonsVL);

    _buttonsVL->addWidget(_regBut);
    _buttonsVL->addWidget(_authBut);
    _buttonsVL->setAlignment(Qt::AlignCenter);
    _mainHL->setAlignment(Qt::AlignCenter);

    connect(_authBut, &QPushButton::clicked, this, &StartFragment::onAuth);
    connect(_regBut, &QPushButton::clicked, this, &StartFragment::onReg);
}

// slots
void StartFragment::onAuth()
{
    emit navigateTo(screens::ScreenNames::LOGIN);
}

void StartFragment::onReg()
{
    emit navigateTo(screens::ScreenNames::REGISTER);
}

} // namespace fragment
