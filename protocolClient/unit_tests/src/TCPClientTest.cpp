#include "gtest/gtest.h"
#include "TCPClientSocket.hpp"
#include "constants.h"

TEST(TCPClientTest, changingPortTest) {
    TCPClientSocket clientSocket;
    EXPECT_EQ(clientSocket.getPort(), TCP_DEFAULT_PORT);
    clientSocket.setPort(TCP_DEFAULT_PORT + 1);
    EXPECT_EQ(clientSocket.getPort(), TCP_DEFAULT_PORT + 1);
}
