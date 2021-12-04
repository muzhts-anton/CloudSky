#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "baseFragment.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QtGui>

namespace fragment {

class GameFragment : public BaseFragment {
    Q_OBJECT
public:
    GameFragment();
    ~GameFragment();

    // void onPause() override;
    // void onResume() override;

public slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void timerOutEvent();

    void onBack();

private:
    QPushButton* _backBut;
    QTimer* _timer;
    bool _butts[9];
};

} // namespace fragment

#endif // GAMEFRAGMENT_H