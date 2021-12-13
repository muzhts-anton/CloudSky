#ifndef MAINFRAGMENT_H
#define MAINFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>

namespace fragment {

class MainFragment : public BaseFragment {
    Q_OBJECT
public:
    MainFragment();
    ~MainFragment();

public slots:
    void onGame();

private:
    QPushButton* _openGameBut;
    QPushButton* _settingsBut;
    QPushButton* _addGameBut;
};

} // namespace fragment

#endif // MAINFRAGMENT_H
