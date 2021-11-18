#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include "basefragment.h"

#include <QPushButton>


class MainFragment : public BaseFragment
{
    Q_OBJECT
public:
    MainFragment();

private slots:
    void goToAddGame();
    void goToOpenGame();
    void quit();

private:
    QPushButton *addGameButton;
    QPushButton *openGameButton;
    QPushButton *quitButton;
};

#endif // MAINFRAGMENT_H
