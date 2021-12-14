#ifndef AUTHFRAGMENT_H
#define AUTHFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLineEdit>
#include <QString>

namespace fragment {

class AuthFragment : public BaseFragment {
    Q_OBJECT
public:
    AuthFragment();
    ~AuthFragment();

public slots:
    void onAuth();

private:
    bool checkData(QString username, QString password);

private:
    QLineEdit* _userName;
    QLineEdit* _userPassword;
    QPushButton* _authBut;
};

} // namespace fragment

#endif
