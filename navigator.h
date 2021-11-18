#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "basefragment.h"
#include "basescreenfactory.h"

#include <QObject>
#include <QStackedWidget>
#include <QLinkedList>

class Navigator : public QObject
{
    Q_OBJECT
public:
    explicit Navigator(QObject *parent = nullptr);
    Navigator(
            QStackedWidget *container,
            BaseScreensFactory *screensFactory
    );
    ~Navigator();
    BaseFragment* getStartScreen();

public slots:
    void navigateTo(QString tag);
    void back();
    void replace(QString tag);
    void newRootScreen(QString tag);
    void backWhithData(BaseModel* model);
    void navigateWhithData(QString tag, BaseModel* model);

private:
    BaseFragment* createAndConnect(QString tag);
    void connectFragment(BaseFragment *fragment);
    void disconnectFragment(BaseFragment *fragment);

private:
    QStackedWidget *currentContainer;
    BaseScreensFactory *screensFactory;
    QList<BaseFragment*> stack;
};

#endif // NAVIGATOR_H
