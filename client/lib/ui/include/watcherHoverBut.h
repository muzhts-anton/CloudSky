#ifndef WATCHERHOVERBUT_H
#define WATCHERHOVERBUT_H

#include <QEvent>
#include <QObject>
#include <QPushButton>

namespace secondfit {

class ButtonHoverWatcher : public QObject {
    Q_OBJECT
public:
    explicit ButtonHoverWatcher(QObject* parent = Q_NULLPTR)
        : QObject(parent) {};
    virtual bool eventFilter(QObject* watched, QEvent* event) Q_DECL_OVERRIDE;

signals:
    void onButHovered(QPushButton* obj);
};

} // namespace secondfit

#endif // WATCHERHOVERBUT_H
