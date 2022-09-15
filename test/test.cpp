#include <gtest/gtest.h>

#include "socket/CSocket.h"
#include "core/core.h"

TEST(SocketClientTest, BasicAssertions) {
    char errorMsg[ERROR_MESSAGE_MAX_LEN];
    memset(errorMsg, 0, sizeof(errorMsg));
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(10000);
    socklen_t sockLen = sizeof(serv_addr);
    status_t status = C_STATUS_ERROR;

    // socket
    c_socket_t socket = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    EXPECT_NE(socket, INVALID_SOCKET);

    // connect
    status = cross_connect_socket(socket, (struct sockaddr*)&serv_addr, sockLen, errorMsg);
    if (status == C_STATUS_ERROR) {
        printf("Error: cross_connect_socket %s \n", errorMsg);
    }
    EXPECT_NE(status, C_STATUS_ERROR);
}

TEST(SocketServerTest, BasicAssertions) {
    char errorMsg[ERROR_MESSAGE_MAX_LEN];
    memset(errorMsg, 0, sizeof(errorMsg));
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(10000);
    socklen_t sockLen = sizeof(serv_addr);
    status_t status = C_STATUS_ERROR;
    c_socket_t newSocket = -1;

    // socket
    c_socket_t socket = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    EXPECT_NE(socket, INVALID_SOCKET);

    // connect
    // status_t status = cross_connect_socket(socket, (struct sockaddr*)&serv_addr, sockLen, errorMsg);
    // if (status == C_STATUS_ERROR) {
    //     printf("Error: cross_connect_socket %s \n", errorMsg);
    // }
    // EXPECT_NE(status, C_STATUS_ERROR);

    // bind
    status = cross_bind_socket(socket, (struct sockaddr*)&serv_addr, sockLen, errorMsg);
    if (status == C_STATUS_ERROR) {
        printf("Error: cross_bind_socket %s \n", errorMsg);
    }
    EXPECT_NE(status, C_STATUS_ERROR);

    // listen
    status = cross_listen_socket(socket, 10, errorMsg);
    if (status == C_STATUS_ERROR) {
        printf("Error: cross_listen_socket %s \n", errorMsg);
    }
    EXPECT_NE(status, C_STATUS_ERROR);

    // accept
    // newSocket = cross_accept_socket(socket, (struct sockaddr*)&serv_addr, &sockLen, errorMsg);
    // if (newSocket == C_STATUS_ERROR) {
    //     printf("Error: cross_accept_socket %s \n", errorMsg);
    // }
    // EXPECT_NE(newSocket, C_STATUS_ERROR);

    // shutdown
    // status = cross_shutdown_socket(socket, SHUT_RDWR, errorMsg);
    // if (status == C_STATUS_ERROR) {
    //     printf("Error: cross_shutdown_socket %s \n", errorMsg);
    // }
    // EXPECT_NE(status, C_STATUS_ERROR);

    // close
    status = cross_close_socket(socket, errorMsg);
    if (status == C_STATUS_ERROR) {
        printf("Error: cross_close_socket %s \n", errorMsg);
    }
    EXPECT_NE(status, C_STATUS_ERROR);
}
