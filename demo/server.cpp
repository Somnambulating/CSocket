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
    fd_set rset;

    // socket
    c_socket_t socketFD = cross_open_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP, errorMsg);
    if (socketFD == C_ERROR) {
        printf("[Error]: cross_open_socket %s \n", errorMsg);
        return -1;
    }

    // setsockopt
    if (cross_setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt), errorMsg) == C_ERROR) {
        printf("[Error]: cross_setsockopt %s \n", errorMsg);
        return -1;
    }

    if (cross_setsockopt(socketFD, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt), errorMsg) == C_ERROR) {
        printf("[Error]: cross_setsockopt %s \n", errorMsg);
        return -1;
    }

    // bind
    status = cross_bind_socket(socketFD, (struct sockaddr*)&serv_addr, sizeof(serv_addr), errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_bind_socket %s \n", errorMsg);
        return -1;
    }

    // listen
    status = cross_listen_socket(socketFD, 10, errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_listen_socket %s \n", errorMsg);
        return -1;
    }

    // FD_ZERO
    cross_FD_ZERO(&rset);

    while (true) {
        // printf("[Waiting...]\n");
        // fflush(stdout);

        // FD_SET
        cross_FD_SET(socketFD, &rset);

        // select
        status = cross_select(socketFD+1, &rset, NULL, NULL, NULL, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_select %s \n", errorMsg);
            break;
        }

        if (cross_FD_ISSET(socketFD, &rset)) {
            // accept
            int newSocketFD = cross_accept_socket(socketFD, (struct sockaddr*)&serv_addr, &addrlen, errorMsg);
            if (newSocketFD == C_ERROR) {
                printf("[Error]: cross_accept_socket %s \n", errorMsg);
                break;
            }

            // recv
            memset(recvBuffer, 0, BUFFER_SIZE);
            status_size = cross_recv_socket(newSocketFD, recvBuffer, BUFFER_SIZE, 0, errorMsg);
            if (status_size == C_ERROR) {
                printf("[Error]: cross_recv_socket %s\n", errorMsg);
                break;
            }

            if (strcmp(recvBuffer, "Bye") == 0) {
                printf("[Message]: End connection soon\n");
                break;
            }
            printf("[Message]: %s\n", recvBuffer);

            // // send
            // memset(sendBuffer, 0, BUFFER_SIZE);
            // fgets(sendBuffer, BUFFER_SIZE, stdin);
            // status_size = cross_send_socket(newSocketFD, sendBuffer, BUFFER_SIZE, 0, errorMsg);
            // if (status_size == C_ERROR) {
            //     printf("[Error]: cross_send_socket %s \n", errorMsg);
            //     break;
            // }
        }
    }

    // shutdown
    if (socketFD != INVALID_SOCKET) {
        status = cross_shutdown_socket(socketFD, SHUT_RDWR, errorMsg);
        if (status == C_ERROR) {
            printf("[Error]: cross_shutdown_socket %s \n", errorMsg);
            return -1;
        }
    }

    // close
    status = cross_close_socket(socketFD, errorMsg);
    if (status == C_ERROR) {
        printf("[Error]: cross_close_socket %s \n", errorMsg);
        return -1;
    }
    return 0;
}