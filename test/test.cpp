#include <gtest/gtest.h>

#include "../src/core.h"
#include "../src/CSocket.h"

TEST(SocketTest, BasicAssertions) {
    char* errorMsg;

    // socket
    c_socket_t socket = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    EXPECT_NE(socket, INVALID_SOCKET);

    // connect
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    socklen_t sockLen = sizeof(serv_addr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    serv_addr.sin_port = htons(10000);
    status_t status = cross_connect_socket(socket, (struct sockaddr*)&serv_addr, sockLen, errorMsg);
    // printf("Error: %s \n", errorMsg);
    EXPECT_NE(status, C_ERROR);

    // bind
    status = cross_bind_socket(socket, (struct sockaddr*)&serv_addr, sockLen, errorMsg);
    printf("Error: %s \n", errorMsg);
    EXPECT_NE(status, C_ERROR);

    // // listen
    // status = cross_listen_socket(socket, 1000, errorMsg);
    // EXPECT_NE(status, C_ERROR);
}
