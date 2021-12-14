#include "watcherHoverBut.h"

namespace secondfit {

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

} // namespace secondfit
