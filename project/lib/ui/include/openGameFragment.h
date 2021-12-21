#ifndef OPENGAMEFRAGMENT_H
#define OPENGAMEFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QPointer>

namespace fragment {

class OpenGameFragment : public BaseFragment {
    Q_OBJECT
public:
    OpenGameFragment();
    ~OpenGameFragment() = default;

public slots:
    void onOpen();
    void onBack();

private:
    void onResume() override;

private:
    QPointer<QLabel> _explanationLabel;
    QPointer<QComboBox> _gameSelecterBox;
    QPointer<QPushButton> _openBut;
    QPointer<QPushButton> _backBut;
};

} // namespace fragment

#endif // OPENGAMEFRAGMENT_H
