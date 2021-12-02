#include "baseFragment.h"

namespace fragment {

void BaseFragment::onPause() { }
void BaseFragment::onResume() { }

void BaseFragment::clearList(QLayout* list)
{
    QLayoutItem* child = nullptr;
    while (list->count()) {
        child = list->takeAt(0);

        if (child->layout())
            clearList(child->layout());
        else if (child->widget())
            delete child->widget();

        delete child;
    }
}

} // namespace fragment
