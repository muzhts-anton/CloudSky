#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "baseFragment.h"
#include "baseScreensFactory.h"
#include "screenNames.h"

#include <QList>
#include <QStackedWidget>

class Navigator : public QObject {
    Q_OBJECT
public:
    Navigator(QStackedWidget* container, BaseScreensFactory* screensFactory);
    Navigator()
        : _container(nullptr)
        , _factory(nullptr) {};
    ~Navigator() = default;

    fragment::BaseFragment* getStartScreen();

public slots:
    void navigateTo(screens::ScreenNames tag);
    void back();
    void replace(screens::ScreenNames tag);
    void newRootScreen(screens::ScreenNames tag);

private:
    fragment::BaseFragment* createAndConnect(screens::ScreenNames tag);
    void connectFragment(fragment::BaseFragment* fragment);
    void disconnectFragment(fragment::BaseFragment* fragment);

private:
    QStackedWidget* _container;
    BaseScreensFactory* _factory;
    QList<fragment::BaseFragment*> _stack;
};

#endif // NAVIGATOR_H
