#ifndef ADDGAMEFRAGMENT_H
#define ADDGAMEFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLabel>
#include <QString>

namespace fragment {

class AddGameFragment : public BaseFragment {
    Q_OBJECT
public:
    AddGameFragment();
    ~AddGameFragment();

public slots:
    void onAddFirst();
    void onAddSecond();
    void onBack();

private:
    QLabel* _cashBalance;
    QLabel* _picFirst;
    QLabel* _picSecond;
    QLabel* _descripFirst;
    QLabel* _descripSecond;
    QPushButton* _addFirstGameBut;
    QPushButton* _addSecondGameBut;
    QPushButton* _backBut;
};

} // namespace fragment

#endif // ADDGAMEFRAGMENT_H
