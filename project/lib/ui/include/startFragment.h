#ifndef STARTFRAGMENT_H
#define STARTFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QPointer>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace fragment {

class StartFragment : public BaseFragment {
    Q_OBJECT
public:
    StartFragment();
    ~StartFragment() = default;

public slots:
    void onAuth();
    void onReg();

private:
    QPointer<QPushButton> _authBut;
    QPointer<QPushButton> _regBut;

    QPointer<QHBoxLayout> _mainHL;
    QPointer<QVBoxLayout> _buttonsVL;
    
};

} // namespace fragment

#endif // STARTFRAGMENT_H
