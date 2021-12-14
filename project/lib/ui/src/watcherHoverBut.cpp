#include <watcherHoverBut.h>

ButtonHoverWatcher::ButtonHoverWatcher(QObject* parent)
    : QObject(parent)
{
}

bool ButtonHoverWatcher::eventFilter(QObject* watched, QEvent* event)
{
    QPushButton* button = qobject_cast<QPushButton*>(watched);
    if (!button)
        return false;

    if (event->type() == QEvent::Enter) {
        emit onButHovered(button);
        return true;
    }

    return false;
}