#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include "baseFragment.h"
#include "watcherHoverBut.h"

#include <QPushButton>
#include <QLabel>

namespace fragment {

class MainFragment : public BaseFragment {
    Q_OBJECT
public:
    MainFragment();
    ~MainFragment();

public slots:
    void onGame();
    void onAddGame();
    void onButHovered(QPushButton* obj);
    void onLogOut();

private:
    QLabel* _greetingLabel;
    QLabel* _pic;
    secondfit::ButtonHoverWatcher* _watcher;
    QPushButton* _openGameBut;
    QPushButton* _settingsBut;
    QPushButton* _addGameBut;
    QPushButton* _logOutBut;
};

} // namespace fragment

#endif // MAINFRAGMENT_H
