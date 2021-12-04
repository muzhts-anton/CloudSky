#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>

namespace fragment {

class StartFragment : public BaseFragment {
    Q_OBJECT
public:
    StartFragment();
    ~StartFragment() { delete _gameBut; }

public slots:
    void onGame();

private:
    QPushButton* _gameBut;
};

} // namespace fragment

#endif // STARTFRAGMENT_H
