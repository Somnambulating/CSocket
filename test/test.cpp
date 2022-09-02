#include <gtest/gtest.h>

#include "../src/CSocket.h"

TEST(SocketTest, BasicAssertions) {
    char errorMsg[512] = {0};
    c_socket_t socket = cross_open_socket(AF_INET, SOCK_STREAM, 0, errorMsg);
    EXPECT_NE(socket, INVALID_SOCKET);
}
