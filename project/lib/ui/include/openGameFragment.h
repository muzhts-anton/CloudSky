#ifndef OPENGAMEFRAGMENT_H
#define OPENGAMEFRAGMENT_H

#include "baseFragment.h"

#include <QPushButton>
#include <QLabel>
#include <QComboBox>

namespace fragment {

class OpenGameFragment : public BaseFragment {
    Q_OBJECT
public:
    OpenGameFragment();
    ~OpenGameFragment();

public slots:
    void onOpen();
    void onBack();

private:
    void onResume() override;

private:
    QLabel* _explanationLabel;
    QComboBox* _gameSelecterBox;
    QPushButton* _openBut;
    QPushButton* _backBut;
};

} // namespace fragment

#endif // OPENGAMEFRAGMENT_H
