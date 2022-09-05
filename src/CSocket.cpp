#include "CSocket.h"

#include "core.h"

typedef int (*c_socket_fn_type)(int domain, int type, int protocol);
c_socket_fn_type c_socket = &socket;

typedef status_t (*c_connect_fn_type)(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen);
c_connect_fn_type c_connect = &connect;

typedef status_t (*c_bind_fn_type)(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen);
c_bind_fn_type c_bind = &bind;

typedef status_t (*c_listen_fn_type)(c_socket_t socket, int backLog);
c_listen_fn_type c_listen = &listen;

typedef status_t (*c_accept_fn_type)(c_socket_t socket, struct sockaddr* addr, socklen_t* addrlen);
c_accept_fn_type c_accept = &accept;

#if defined(DARWIN)
typedef status_t (*c_close_socket_fn_type)(c_socket_t socket);
c_close_socket_fn_type c_close_socket = &close;
#elif defined(WINDOWS)
typedef status_t (*c_close_socket_fn_type)(c_socket_t socket);
c_close_socket_fn_type c_close_socket = &closesocket;
#elif defined(LINUX)
typedef status_t (*c_close_socket_fn_type)(c_socket_t socket);
c_close_socket_fn_type c_close_socket = &close;
#endif

typedef status_t (*c_shutdown_socket_fn_type)(c_socket_t socket, int how);
c_shutdown_socket_fn_type c_shutdown_socket = &shutdown;

// TODO: In windows, the type of return value is int not ssize_t
typedef ssize_t (*c_recv_fn_type)(c_socket_t socket, void* buf, size_t len, int flags);
c_recv_fn_type c_recv = &recv;

// TODO: In windows, the type of return value is int not ssize_t
typedef ssize_t (*c_recvfrom_fn_type)(c_socket_t socket, void* buf, size_t len, int flags, struct sockaddr* src_addr, socklen_t* addrlen);
c_recvfrom_fn_type c_recvfrom = &recvfrom;

// TODO: In windows, the type of return value is int not ssize_t
typedef ssize_t (*c_send_fn_type)(c_socket_t socket, const void* buf, size_t len, int flags);
c_send_fn_type c_send = &send;

// TODO: In windows, the type of return value is int not ssize_t
typedef ssize_t (*c_sendto_fn_type)(c_socket_t socket, const void* buf, size_t len, int flags, const struct sockaddr* dest_addr, socklen_t addrlen);
c_sendto_fn_type c_sendto = &sendto;

typedef int (*c_getaddrinfo_fn_type)(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res);
c_getaddrinfo_fn_type c_getaddrinfo = &getaddrinfo;

typedef void (*c_freeaddrinfo_fn_type)(struct addrinfo* ai);
c_freeaddrinfo_fn_type c_freeaddrinfo = &freeaddrinfo;

#if defined(DARWIN)
typedef int (*c_setsockopt_fn_type)(c_socket_t socket, int level, int option_name, const void* option_value, socklen_t option_len);
c_setsockopt_fn_type c_setsockopt = &setsockopt;
typedef int (*c_getsockopt_fn_type)(c_socket_t socket, int level, int option_name, void* option_value, socklen_t* option_len);
c_getsockopt_fn_type c_getsockopt = &getsockopt;
#elif defined(WINDOWS)
typedef int (*c_setsockopt_fn_type)(c_socket_t socket, int level, int option_name, const char* option_value, int option_len);
c_setsockopt_fn_type c_setsockopt = &setsockopt;
typedef int (*c_getsockopt_fn_type)(c_socket_t socket, int level, int option_name, char* option_value, int* option_len);
c_getsockopt_fn_type c_getsockopt = &getsockopt;
#elif defined(LINUX)
typedef int (*c_setsockopt_fn_type)(c_socket_t socket, int level, int option_name, const void* option_value, socklen_t option_len);
c_setsockopt_fn_type c_setsockopt = &setsockopt;
typedef int (*c_getsockopt_fn_type)(c_socket_t socket, int level, int option_name, void* option_value, socklen_t* option_len);
c_getsockopt_fn_type c_getsockopt = &getsockopt;
#endif

#if defined(DARWIN)
typedef int (*c_select_fn_type)(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval* timeout);
c_select_fn_type c_select = &select;
#elif defined(WINDOWS)
typedef int (*c_select_fn_type)(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, const struct timeval* timeout);
c_select_fn_type c_select = &select;
#elif defined(LINUX)
typedef int (*c_select_fn_type)(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval* timeout);
c_select_fn_type c_select = &select;
#endif

#define c_FD_CLR FD_CLR
#define c_FD_ISSET FD_ISSET
#define c_FD_SET FD_SET
#define c_FD_ZERO FD_ZERO

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
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return socket;
}

// TODO
status_t cross_connect_socket(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_connect(socket, addr, addrlen);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
status_t cross_bind_socket(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_bind(socket, addr, addrlen);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
status_t cross_listen_socket(c_socket_t socket, int backlog, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_listen(socket, backlog);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
status_t cross_accept_socket(c_socket_t socket, struct sockaddr* addr, socklen_t* addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_accept(socket, addr, addrlen);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
status_t cross_close_socket(c_socket_t socket, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_close_socket(socket);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
status_t cross_shutdown_socket(c_socket_t socket, int how, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_shutdown_socket(socket, how);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
ssize_t cross_recv_socket(c_socket_t socket, void* buf, size_t len, int flags, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_recv(socket, buf, len, flags);
    // printf("[c_recv]: %s\n", (char*)buf);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
ssize_t cross_recvfrom_socket(c_socket_t socket, void* buf, size_t len, int flags, struct sockaddr* src_addr, socklen_t* addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_recvfrom(socket, buf, len, flags, src_addr, addrlen);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
ssize_t cross_send_socket(c_socket_t socket, void* buf, size_t len, int flags, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_send(socket, buf, len, flags);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
ssize_t cross_sendto_socket(c_socket_t socket, void* buf, size_t len, int flags, struct sockaddr* dest_addr, socklen_t addrlen, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_sendto(socket, buf, len, flags, dest_addr, addrlen);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
int cross_setsockopt(c_socket_t socket, int level, int option_name, const void* option_value, socklen_t option_len, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_setsockopt(socket, level, option_name, option_value, option_len);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
int cross_getsockopt(c_socket_t socket, int level, int option_name, void* option_value, socklen_t* option_len, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_getsockopt(socket, level, option_name, option_value, option_len);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

// TODO
int cross_select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval* timeout, char* errorMsg) {
    status_t status = C_ERROR;
    status = c_select(nfds, readfds, writefds, errorfds, timeout);
    if (status == C_ERROR) {
#if defined(DARWIN)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#elif defined(WINDOWS)
// TODO
#elif defined(LINUX)
        memcpy(errorMsg, strerror(errno), ERROR_MESSAGE_MAX_LEN);
#endif
    }

    return status;
}

void cross_FD_CLR(c_socket_t fd, fd_set* set) {
    c_FD_CLR(fd, set);
}

int cross_FD_ISSET(c_socket_t fd, fd_set* set) {
    return c_FD_ISSET(fd, set);
}

void cross_FD_SET(c_socket_t fd, fd_set* set) {
    c_FD_SET(fd, set);
}

void cross_FD_ZERO(fd_set* set) {
    c_FD_ZERO(set);
}