#ifndef SETTINGSFRAGMENT_H
#define SETTINGSFRAGMENT_H

#include "basefragment.h"

#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>


class SettingsFragment : public BaseFragment
{
    Q_OBJECT
public:
    SettingsFragment();

private slots:
    void volumeChanged();
    void screenResChanged();
    void addButtonPressed();
    void quit();

private:
    void sendToDB();

private:
    QSpinBox *volumeBox;
    QComboBox *sreenResolution;
    QLabel *stats;
    QPushButton *quit;
};

#endif // SETTINGSFRAGMENT_H
