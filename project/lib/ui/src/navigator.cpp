#include "navigator.h"

#include <QDebug>

Navigator::Navigator(QStackedWidget* container, ScreensFactory* factory)
    : _container(container)
    , _factory(factory)
{
    _stack.append(this->getStartScreen());

    _container->addWidget(_stack.last());
    _container->setCurrentIndex(0);
}

// slots
void Navigator::navigateTo(screens::ScreenNames tag)
{
    _stack.last()->onPause();
    disconnectFragment(_stack.last());

    fragment::BaseFragment* newFragment = _factory->create(tag);
    connectFragment(newFragment);
    _stack.append(newFragment);
    _container->addWidget(newFragment);
    _container->setCurrentWidget(newFragment);
}

void Navigator::back()
{
    _container->removeWidget(_stack.last());
    delete _stack.last();
    _stack.removeLast();

    connectFragment(_stack.last());
    _stack.last()->onResume();
    _container->setCurrentWidget(_stack.last());
}

void Navigator::replace(screens::ScreenNames tag)
{
    _container->removeWidget(_stack.last());
    delete _stack.last();
    _stack.removeLast();

    fragment::BaseFragment* newFragment = _factory->create(tag);
    connectFragment(newFragment);
    _container->addWidget(newFragment);
}

void Navigator::newRootScreen(screens::ScreenNames tag)
{
    disconnectFragment(_stack.last());
    _stack.clear();

    fragment::BaseFragment* newFragment = _factory->create(tag);
    connectFragment(newFragment);

    for (int i = _container->count(); i >= 0; --i) {
        QWidget* widget = _container->widget(i);
        _container->removeWidget(widget);
        widget->deleteLater();
    }

    _container->addWidget(newFragment);
    _stack.append(newFragment);
}

fragment::BaseFragment* Navigator::getStartScreen()
{
    return createAndConnect(_factory->getStart());
}

void Navigator::connectFragment(fragment::BaseFragment* fragment)
{
    connect(fragment, &fragment::BaseFragment::back, this, &Navigator::back);
    connect(fragment, &fragment::BaseFragment::replace, this, &Navigator::replace);
    connect(fragment, &fragment::BaseFragment::navigateTo, this, &Navigator::navigateTo);
    connect(fragment, &fragment::BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
}

void Navigator::disconnectFragment(fragment::BaseFragment* fragment)
{
    disconnect(fragment, &fragment::BaseFragment::back, this, &Navigator::back);
    disconnect(fragment, &fragment::BaseFragment::replace, this, &Navigator::replace);
    disconnect(fragment, &fragment::BaseFragment::navigateTo, this, &Navigator::navigateTo);
    disconnect(fragment, &fragment::BaseFragment::newRootScreen, this, &Navigator::newRootScreen);
}

fragment::BaseFragment* Navigator::createAndConnect(screens::ScreenNames tag)
{
    fragment::BaseFragment* fragment = _factory->create(tag);
    connectFragment(fragment);
    return fragment;
}
