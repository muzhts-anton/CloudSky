#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include "baseFragment.h"
#include "watcherHoverBut.h"

#include <QPushButton>
#include <QLabel>
#include <QPointer>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace fragment {

class MainFragment : public BaseFragment {
    Q_OBJECT
public:
    MainFragment();
    ~MainFragment() = default;

public slots:
    void onGame();
    void onAddGame();
    void onButHovered(QPushButton* obj);
    void onLogOut();

private:
    QPointer<QLabel> _greetingLabel;
    QPointer<QLabel> _pic;
    QPointer<secondfit::ButtonHoverWatcher> _watcher;
    QPointer<QPushButton> _openGameBut;
    QPointer<QPushButton> _settingsBut;
    QPointer<QPushButton> _addGameBut;
    QPointer<QPushButton> _logOutBut;

    QPointer<QHBoxLayout> _mainHL;
    QPointer<QVBoxLayout> _buttonsVL;
};

} // namespace fragment

#endif // MAINFRAGMENT_H
