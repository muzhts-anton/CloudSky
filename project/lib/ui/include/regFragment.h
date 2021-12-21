#ifndef REGFRAGMENT_H
#define REGFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QPointer>

namespace fragment {

class RegFragment : public BaseFragment {
    Q_OBJECT
public:
    RegFragment();
    ~RegFragment() = default;

public slots:
    void onReg();
    void onBack();

private:
    void onResume() override;

private:
    bool checkData();

private:
    QPointer<QLabel> _explanLabel;
    QPointer<QLineEdit> _userFirstName;
    QPointer<QLineEdit> _userSecondName;
    QPointer<QLineEdit> _userCountry;
    QPointer<QLineEdit> _userEmail;
    QPointer<QLineEdit> _userNickName;
    QPointer<QLineEdit> _userFirstPassword;
    QPointer<QLineEdit> _userSecondPassword;
    QPointer<QLabel> _ageTxt;
    QPointer<QSpinBox> _userAge;
    QPointer<QLabel> _errorLabel;
    QPointer<QPushButton> _regBut;
    QPointer<QPushButton> _backBut;
};

} // namespace fragment

#endif // REGFRAGMENT_H
