#ifdef UNIX

#include <assert.h>
#include <string.h>
#include "error.h"
#include "socket_imp_unix.h"

SocketUnixImp::SocketUnixImp() {}

SocketUnixImp::SocketUnixImp(const char* address, in_port_t port, sa_family_t family) {
    assert(strlen(address) < 17);
    assert(port != 0);
    memcpy(socket_info_.address_, address, 16);
    socket_info_.port_ = port;
    socket_info_.family_ = family;
}

SocketUnixImp::~SocketUnixImp() {}

c_socket_t SocketUnixImp::open_socket(int domain, int type, int protocol) {
    socket_info_.sock_fd_ = ::socket(domain, type, protocol);
    return socket_info_.sock_fd_;
}

status_t SocketUnixImp::connect() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = socket_info_.family_;
    addr.sin_addr.s_addr = inet_addr(socket_info_.address_);
    addr.sin_port = htons(socket_info_.port_);
    socklen_t addrLen = sizeof(addr);

    return ::connect(socket_info_.sock_fd_, (struct sockaddr*)&addr, addrLen);
}

status_t SocketUnixImp::bind() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = socket_info_.family_;
    addr.sin_addr.s_addr = inet_addr(socket_info_.address_);
    addr.sin_port = htons(socket_info_.port_);
    socklen_t addrLen = sizeof(addr);

    return ::bind(socket_info_.sock_fd_, (struct sockaddr*)&addr, addrLen);
}

status_t SocketUnixImp::listen(int backlog) {
    return ::listen(socket_info_.sock_fd_, backlog);
}

c_socket_t SocketUnixImp::accept() {
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = socket_info_.family_;
    addr.sin_addr.s_addr = inet_addr(socket_info_.address_);
    addr.sin_port = htons(socket_info_.port_);
    socklen_t addrLen = sizeof(addr);

    socket_info_.new_sock_fd_ = ::accept(socket_info_.sock_fd_, (struct sockaddr*)&addr, &addrLen);
    return socket_info_.new_sock_fd_;
}

status_t SocketUnixImp::shutdown(int how) {
    return ::shutdown(socket_info_.sock_fd_, how);
}

status_t SocketUnixImp::close() {
    return ::close(socket_info_.sock_fd_);
}

status_t SocketUnixImp::setsockopt(int level, int option_name, const void *option_value, socklen_t option_len) {
    return ::setsockopt(socket_info_.sock_fd_, level, option_name, option_value, option_len);
}

#endif