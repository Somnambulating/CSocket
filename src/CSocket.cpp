#include "CSocket.h"

#include "core.h"

typedef int (*c_socket_fn_type)(int domain, int type, int protocol);
c_socket_fn_type c_socket = &socket;

typedef status_t (*c_connect_fn_type)(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen);
c_connect_fn_type c_connect = &connect;

#define c_bind bind

#define c_listen listen

#define c_accept accept

#if defined(DARWIN)
#define c_close_socket close
#elif defined(WINDOWS)
#define c_close_socket closesocket
#elif defined(LINUX)
#define c_close_socket close
#endif

#define c_shutdown_socket shutdown

#define c_recv recv

#define c_send send

typedef int (*c_getaddrinfo_fn_type)(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res);
c_getaddrinfo_fn_type c_getaddrinfo = &getaddrinfo;

typedef void (*c_freeaddrinfo_fn_type)(struct addrinfo* ai);
c_freeaddrinfo_fn_type c_freeaddrinfo = &freeaddrinfo;


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
        perror("Invalid socket.\n");
    }

    return socket;
}

// TODO
status_t cross_connect_socket(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_connect(socket, addr, addrlen);
    if (status == C_ERROR) {
        perror("Invalid socket.\n");
    }

    return status;
}