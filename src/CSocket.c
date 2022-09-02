#include "CSocket.h"

#include "core.h"

// TODO
status_t cross_getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_getaddrinfo(node, service, hints, res);
    if (status == C_ERROR) {
    }

    return status;
}

// TODO
void cross_freeaddrinfo(struct addrinfo* ai, char* errorMsg) {
    c_freeaddrinfo(ai);
}

// TODO
c_socket_t cross_open_socket(int domain, int type, int protocol, char* errorMsg) {
    c_socket_t socket = INVALID_SOCKET;
    socket = c_socket(domain, type, protocol);
    if (socket == INVALID_SOCKET) {
    }

    return socket;
}