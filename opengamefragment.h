#ifndef OPENGAMEFRAGMENT_H
#define OPENGAMEFRAGMENT_H

#include "basefragment.h"

#include <QComboBox>
#include <QPushButton>
#include <QLabel>


class OpenGameFragment : public BaseFragment
{
    Q_OBJECT
public:
    OpenGameFragment();

private slots:
    void playButtonPressed();
    void quit();

private:
    QComboBox *game;
    QLabel *description;
    QPushButton *play;
    QPushButton *quit;
};

#endif // OPENGAMEFRAGMENT_H
