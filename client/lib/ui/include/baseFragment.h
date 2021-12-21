#ifndef BASEFRAGMENT_H
#define BASEFRAGMENT_H

#include "screenNames.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QWidget>

namespace fragment {

class BaseFragment : public QFrame {
    Q_OBJECT
public:
    BaseFragment() = default;
    ~BaseFragment() = default;

    virtual void onPause();
    virtual void onResume();

signals:
    void navigateTo(screens::ScreenNames tag);
    void back();
    void replace(screens::ScreenNames tag);
    void newRootScreen(screens::ScreenNames tag);

protected:
    void clearList(QLayout* list);
};

} // namespace fragment

#endif // BASEFRAGMENT_H