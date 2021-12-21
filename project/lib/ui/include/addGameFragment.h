#ifndef ADDGAMEFRAGMENT_H
#define ADDGAMEFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPointer>

namespace fragment {

class AddGameFragment : public BaseFragment {
    Q_OBJECT
public:
    AddGameFragment();
    ~AddGameFragment() = default;

public slots:
    void onAddFirst();
    void onAddSecond();
    void onBack();

private:
    QPointer<QLabel> _cashBalance;
    QPointer<QLabel> _picFirst;
    QPointer<QLabel> _picSecond;
    QPointer<QLabel> _descripFirst;
    QPointer<QLabel> _descripSecond;
    QPointer<QPushButton> _addFirstGameBut;
    QPointer<QPushButton> _addSecondGameBut;
    QPointer<QPushButton> _backBut;
};

} // namespace fragment

#endif // ADDGAMEFRAGMENT_H
