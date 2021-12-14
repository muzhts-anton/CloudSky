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
    void onButHovered(QPushButton* obj);

private:
    QLabel* _pic;
    secondfit::ButtonHoverWatcher* _watcher;
    QPushButton* _openGameBut;
    QPushButton* _settingsBut;
    //QPushButton* _addGameBut;
};

} // namespace fragment

#endif // MAINFRAGMENT_H
