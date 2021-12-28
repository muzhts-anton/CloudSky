#include "baseFragment.h"

namespace fragment {

constexpr const char *serverIP = "10.147.18.164";
constexpr int serverPort = 8085;
TCPClient::TCPClientSocket *BaseFragment::TCPSocket = new TCPClient::TCPClientSocket(serverPort, serverIP);

// TODO(Tony): = 0 or in .h. This looks ugly
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
