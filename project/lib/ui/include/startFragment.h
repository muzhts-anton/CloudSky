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
    void onAuth();
    void onReg();

private:
    QPushButton* _authBut;
    QPushButton* _regBut;
};

} // namespace fragment

#endif // STARTFRAGMENT_H
