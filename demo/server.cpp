#include "../src/CSocket.h"
#include "../src/core.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

int main() {
    char errorMsg[ERROR_MESSAGE_MAX_LEN];
    memset(errorMsg, 0, ERROR_MESSAGE_MAX_LEN);
    struct sockaddr_in serv_addr;
    socklen_t addrlen = sizeof(serv_addr);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(10001);
    status_t status = C_ERROR;
    char recvBuffer[BUFFER_SIZE];
    char sendBuffer[BUFFER_SIZE];
    int opt = 1;
    ssize_t status_size = -1;

    // socket
    c_socket_t socket = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    if (socket == C_ERROR) {
        printf("[Error]: cross_open_socket %s \n", errorMsg);
        return -1;
    }

    if (cross_setsockopt(socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt), errorMsg) == C_ERROR) {
        printf("[Error]: cross_setsockopt %s \n", errorMsg);
        return -1;
    }

    // bind
    status = cross_bind_socket(socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr), errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_bind_socket %s \n", errorMsg);
        return -1;
    }

    // listen
    status = cross_listen_socket(socket, 10, errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_listen_socket %s \n", errorMsg);
        return -1;
    }

    while (true) {
        printf("[Waiting...]\n");
        fflush(stdout);

        // accept
        int newSocket = cross_accept_socket(socket, (struct sockaddr*)&serv_addr, &addrlen, errorMsg);
        if (newSocket == C_ERROR) {
            printf("[Error]: cross_accept_socket %s \n", errorMsg);
            break;
        }

        // recv
        memset(recvBuffer, 0, BUFFER_SIZE);
        status_size = cross_recv_socket(newSocket, recvBuffer, BUFFER_SIZE, 0, errorMsg);
        if (status_size == C_ERROR) {
            printf("[Error]: cross_recv_socket %s\n", errorMsg);
            break;
        }

        if (strcmp(recvBuffer, "Bye") == 0) {
            printf("[Message]: End connection soon\n");
            break;
        }
        printf("[Message]: %s\n", recvBuffer);

        // send
        memset(sendBuffer, 0, BUFFER_SIZE);
        fgets(sendBuffer, BUFFER_SIZE, stdin);
        status_size = cross_send_socket(newSocket, sendBuffer, BUFFER_SIZE, 0, errorMsg);
        if (status_size == C_ERROR) {
            printf("[Error]: cross_send_socket %s \n", errorMsg);
            break;
        }
    }

    // shutdown
    if (socket != INVALID_SOCKET) {
        status = cross_shutdown_socket(socket, SHUT_RDWR, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_shutdown_socket %s \n", errorMsg);
            return -1;
        }
    }

    // close
    status = cross_close_socket(socket, errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_close_socket %s \n", errorMsg);
        return -1;
    }
    return 0;
}