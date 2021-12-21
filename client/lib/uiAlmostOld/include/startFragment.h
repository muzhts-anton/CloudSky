#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>

namespace fragment {

class StartFragment : public BaseFragment {
    Q_OBJECT
public:
    StartFragment();
    ~StartFragment();

public slots:
    void onGame();

private:
    QPushButton* _openGameBut;
    QPushButton* _settingsBut;
    QPushButton* _addGameBut;
};

} // namespace fragment

#endif // STARTFRAGMENT_H
