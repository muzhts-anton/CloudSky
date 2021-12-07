#ifndef GAMEFRAGMENT_H
#define GAMEFRAGMENT_H

#include "baseFragment.h"
#include "SDLWidget.h"

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
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void timerOutEvent();

    void onBack();

private:
    static constexpr short fps = 80;
    enum class Buttons {
        A = 0,
        W,
        S,
        D,
        SPACE,
        Q,
        E,
        F,
        ESC,
        COUNT,
    };
    enum class Mouse {
        RIGHT = 0,
        LEFT,
        COUNT,
    };

private:
    //QSDLScreenWidget* _player;
    QPushButton* _backBut;
    QTimer* _timer;
    bool _butts[(size_t)Buttons::COUNT];
    bool _mouse[(size_t)Mouse::COUNT];
};

} // namespace fragment

#endif // GAMEFRAGMENT_H