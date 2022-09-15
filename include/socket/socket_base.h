#ifndef SOCKET_BASE_H_
#define SOCKET_BASE_H_

#include "core/core.h"

// TODO: ipv6
struct SocketInfo {
    c_socket_t sock_fd;
    c_socket_t new_sock_fd;
    char address[16];
    in_port_t port;
    sa_family_t family;
};

class SocketBase {
   public:
    virtual c_socket_t open_socket(int domain, int type, int protocol) = 0;
    virtual status_t connect() = 0;
    virtual status_t bind() = 0;
    virtual status_t listen(int backlog) = 0;
    virtual c_socket_t accept() = 0;
    virtual status_t shutdown(int how) = 0;
    virtual status_t close() = 0;
};

#endif /* SOCKET_BASE_H_ */