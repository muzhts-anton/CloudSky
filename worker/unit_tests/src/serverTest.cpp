#include "gtest/gtest.h"
#include "Server.hpp"
#include "constants.hpp"

TEST(protocolServer, changingPortTest) {
    Server server;
    EXPECT_EQ(server.getPort(), SERVER_IS_NOT_RUNNING);
    server.setPort(5005);
    EXPECT_EQ(server.getPort(), 5005);
}

TEST(protocolServer, serverStatusTest) {
    Server server;
    EXPECT_EQ(server.getStatus(), SHUT_DOWN);
    server.start();
    EXPECT_EQ(server.getStatus(), RUNNING);
    server.restart();
    EXPECT_EQ(server.getStatus(), RUNNING);
    server.stop();
    EXPECT_EQ(server.getStatus(), STOPPED);
}

