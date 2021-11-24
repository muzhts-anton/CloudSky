#include "gtest/gtest.h"
#include "UDPClientSocket.hpp"
#include "constants.h"

TEST(UPDClientTest, changingPortTest) {
    UDPClientSocket clientSocket;
    EXPECT_EQ(clientSocket.getPort(), UDP_DEFAULT_PORT);
    clientSocket.setPort(UDP_DEFAULT_PORT + 1);
    EXPECT_EQ(clientSocket.getPort(), UDP_DEFAULT_PORT + 1);
}
