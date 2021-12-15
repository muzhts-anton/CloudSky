#ifndef AUTHFRAGMENT_H
#define AUTHFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>

namespace fragment {

class AuthFragment : public BaseFragment {
    Q_OBJECT
public:
    AuthFragment();
    ~AuthFragment();

public slots:
    void onAuth();
    void onBack();

private:
    void onResume() override;

private:
    bool checkData();

private:
    QLabel* _explanLabel;
    QLineEdit* _userName;
    QLineEdit* _userPassword;
    QPushButton* _authBut;
    QPushButton* _backBut;
};

} // namespace fragment

#endif // AUTHFRAGMENT_H
