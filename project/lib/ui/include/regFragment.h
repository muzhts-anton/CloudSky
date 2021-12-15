#ifndef REGFRAGMENT_H
#define REGFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QString>

namespace fragment {

class RegFragment : public BaseFragment {
    Q_OBJECT
public:
    RegFragment();
    ~RegFragment();

public slots:
    void onReg();

private:
    bool checkData(QString username, QString password);

private:
    QLineEdit* _userFirstName;
    QLineEdit* _userSecondName;
    QLineEdit* _userNickName;
    QLineEdit* _userFirstPassword;
    QLineEdit* _userSecondPassword;
    QLabel* _ageTxt;
    QSpinBox* _userAge;
    QPushButton* _regBut;
};

} // namespace fragment

#endif // REGFRAGMENT_H
