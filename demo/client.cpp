#include "../src/CSocket.h"
#include "../src/core.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

int main() {
    char errorMsg[ERROR_MESSAGE_MAX_LEN];
    memset(errorMsg, 0, sizeof(errorMsg));
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(10001);
    socklen_t addrLen = sizeof(serv_addr);
    status_t status = C_ERROR;
    char recvBuffer[BUFFER_SIZE];
    char sendBuffer[BUFFER_SIZE];
    ssize_t status_size = -1;

    // socket
    c_socket_t socketFd = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    if (socketFd == C_ERROR) {
        printf("[Error]: cross_open_socket %s \n", errorMsg);
        return -1;
    }

    // connect
    status = cross_connect_socket(socketFd, (struct sockaddr*)&serv_addr, addrLen, errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_connect_socket %s \n", errorMsg);
        return -1;
    }

    sleep(1);

    do {
        // send
        memset(sendBuffer, 0, BUFFER_SIZE);
        fgets(sendBuffer, BUFFER_SIZE, stdin);
        status_size = cross_send_socket(socketFd, sendBuffer, BUFFER_SIZE, 0, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_send_socket %s \n", errorMsg);
            break;
        }

        // recv
        memset(recvBuffer, 0, BUFFER_SIZE);
        status_size = cross_recv_socket(socketFd, recvBuffer, BUFFER_SIZE, 0, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_recv_socket %s \n", errorMsg);
            break;
        }

        printf("[Message]: %s\n", recvBuffer);

    } while (status_size != C_ERROR);

    // shutdown
    if (socketFd != INVALID_SOCKET) {
        status = cross_shutdown_socket(socketFd, SHUT_RDWR, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_shutdown_socket %s \n", errorMsg);
            return -1;
        }
    }

    // close
    status = cross_close_socket(socketFd, errorMsg);
    if (status == C_ERROR) {
        printf("Error: cross_close_socket %s \n", errorMsg);
        return -1;
    }
    return 0;
}