#ifndef AUTHFRAGMENT_H
#define AUTHFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include <QPointer>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace fragment {

class AuthFragment : public BaseFragment {
    Q_OBJECT
public:
    AuthFragment();
    ~AuthFragment() = default;

public slots:
    void onAuth();
    void onBack();

private:
    void onResume() override;

private:
    bool checkData();

private:
    QPointer<QLabel> _explanLabel;
    QPointer<QLineEdit> _userName;
    QPointer<QLineEdit> _userPassword;
    QPointer<QPushButton> _authBut;
    QPointer<QPushButton> _backBut;

    QPointer<QHBoxLayout> _buttsHL;
    QPointer<QVBoxLayout> _mainVL;
};

} // namespace fragment

#endif // AUTHFRAGMENT_H
