#ifndef ADDGAMEFRAGMENT_H
#define ADDGAMEFRAGMENT_H

#include "basefragment.h"

#include <QLineEdit>
#include <QPushButton>


class AddGameFragment : public BaseFragment
{
    Q_OBJECT
public:
    AddGameFragment();

private slots:
    void quit()
    void addButtonPressed();

private:
    QLineEdit *pathToGame;
    QPushButton *addButton;
    QPushButton *quit;
};

#endif // ADDGAMEFRAGMENT_H
