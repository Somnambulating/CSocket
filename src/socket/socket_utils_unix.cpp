#ifdef UNIX

#include "socket/socket_utils_unix.h"

#include "core/core.h"
#include "core/port.h"

error_handle_t c_set_socket_zerocopy(c_socket_t fd) {
#ifdef C_LINUX_ERRQUEUE
  const int enable = 1;
  auto err = setsockopt(fd, SOL_SOCKET, SO_ZEROCOPY, &enable, sizeof(enable));
  if (err != 0) {
    return C_ERROR(errno, "setsockopt(SO_ZEROCOPY)");
  }
  return C_ERROR_NONE;
#else
  (void)fd;
  return C_ERROR(ENOSYS, "setsockopt(SO_ZEROCOPY)");
#endif
}

error_handle_t c_set_socket_nonblocking(c_socket_t fd, int non_blocking) {
    int oldflags = fcntl(fd, F_GETFL, 0);
    if (oldflags < 0) {
        return C_ERROR(errno, "fcntl");
    }

    if (non_blocking) {
        oldflags |= O_NONBLOCK;
    } else {
        oldflags &= ~O_NONBLOCK;
    }

    if (fcntl(fd, F_SETFL, oldflags) != 0) {
        return C_ERROR(errno, "fcntl");
    }

    return C_ERROR_NONE;
}

error_handle_t c_set_socket_no_sigpipe_if_possible(c_socket_t fd) {
#ifdef C_HAVE_SO_NOSIGPIPE
    int val = 1;
    int newval;
    c_socket_t intlen = sizeof(newval);
    if (0 != setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof(val))) {
        return C_ERROR(errno, "getsockopt(SO_NOSIGPIPE)");
    }
    if (0 != getsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &newval, &intlen)) {
        return C_ERROR(errno, "getsockopt(SO_NOSIGPIPE)");
    }
    if ((newval != 0) != (val != 0)) {
        return C_ERROR(errno, "getsockopt(SO_NOSIGPIPE)");
    }
#else
    // Avoid unused parameter warning for conditional parameter
#endif
    return C_ERROR_NONE;
}

error_handle_t c_set_socket_ip_pktinfo_if_possible(c_socket_t fd) {
    // Use conditionally-important parameter to avoid warning
#ifdef C_HAVE_IP_PKTINFO
    int get_local_ip = 1;
    if (0 != setsockopt(fd, IPPROTO_IP, IP_PKTINFO, &get_local_ip,
                        sizeof(get_local_ip))) {
        return C_ERROR(errno, "setsockopt(IP_PKTINFO)");
    }
#endif
    return C_ERROR_NONE;
}

error_handle_t c_set_socket_ipv6_recvpktinfo_if_possible(c_socket_t fd) {
    // Use conditionally-important parameter to avoid warning
#ifdef C_HAVE_IPV6_RECVPKTINFO
    int get_local_ip = 1;
    if (0 != setsockopt(fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, &get_local_ip,
                        sizeof(get_local_ip))) {
        return C_ERROR(errno, "setsockopt(IPV6_RECVPKTINFO)");
    }
#endif
    return C_ERROR_NONE;
}

error_handle_t c_set_socket_sndbuf(c_socket_t fd, int buffer_size_bytes) {
    return 0 == setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buffer_size_bytes,
                           sizeof(buffer_size_bytes))
               ? C_ERROR_NONE
               : C_ERROR(errno, "setsockopt(SO_SNDBUF)");
}

error_handle_t c_set_socket_rcvbuf(c_socket_t fd, int buffer_size_bytes) {
    return 0 == setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &buffer_size_bytes,
                           sizeof(buffer_size_bytes))
               ? C_ERROR_NONE
               : C_ERROR(errno, "setsockopt(SO_RCVBUF)");
}

error_handle_t c_set_socket_cloexec(c_socket_t fd, int close_on_exec) {
    int oldflags = fcntl(fd, F_GETFD, 0);
    if (oldflags < 0) {
        return C_ERROR(errno, "fcntl");
    }

    if (close_on_exec) {
        oldflags |= FD_CLOEXEC;
    } else {
        oldflags &= ~FD_CLOEXEC;
    }

    if (fcntl(fd, F_SETFD, oldflags) != 0) {
        return C_ERROR(errno, "fcntl");
    }

    return C_ERROR_NONE;
}

error_handle_t c_set_socket_reuse_addr(c_socket_t fd, int reuse) {
    int val = (reuse != 0);
    int newval;
    socklen_t intlen = sizeof(newval);
    if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))) {
        return C_ERROR(errno, "setsockopt(SO_REUSEADDR)");
    }
    if (0 != getsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &newval, &intlen)) {
        return C_ERROR(errno, "setsockopt(SO_REUSEADDR)");
    }
    if ((newval != 0) != val) {
        return C_ERROR(C_STATUS_ERROR, "Failed to set SO_REUSEADDR");
    }

    return C_ERROR_NONE;
}

error_handle_t c_set_socket_reuse_port(c_socket_t fd, int reuse) {
#ifndef SO_REUSEPORT
    // "SO_REUSEPORT unavailable on compiling system"
    return C_STATUS_ERROR;
#else
    int val = (reuse != 0);
    int newval;
    socklen_t intlen = sizeof(newval);
    if (0 != setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val))) {
        return C_ERROR(errno, "setsockopt(SO_REUSEPORT)");
    }
    if (0 != getsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &newval, &intlen)) {
        return C_ERROR(errno, "setsockopt(SO_REUSEPORT)");
    }
    if ((newval != 0) != val) {
        return C_ERROR(C_STATUS_ERROR, "Failed to set SO_REUSEPORT");
    }

    return C_ERROR_NONE;
#endif
}

error_handle_t c_set_socket_low_latency(c_socket_t fd, int low_latency) {
    int val = (low_latency != 0);
    int newval;
    socklen_t intlen = sizeof(newval);
    if (0 != setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val))) {
        return C_ERROR(errno, "setsockopt(TCP_NODELAY)");
    }
    if (0 != getsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &newval, &intlen)) {
        return C_ERROR(errno, "setsockopt(TCP_NODELAY)");
    }
    if ((newval != 0) != val) {
        return C_ERROR(C_STATUS_ERROR, "Failed to set TCP_NODELAY");
    }
    return C_ERROR_NONE;
}

/* The default values for TCP_USER_TIMEOUT are currently configured to be in
 * line with the default values of KEEPALIVE_TIMEOUT as proposed in
 * https://github.com/c/proposal/blob/master/A18-tcp-user-timeout.md */
#define DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS 20000 /* 20 seconds */
#define DEFAULT_SERVER_TCP_USER_TIMEOUT_MS 20000 /* 20 seconds */

static int c_default_client_tcp_user_timeout_ms =
    DEFAULT_CLIENT_TCP_USER_TIMEOUT_MS;
static int c_default_server_tcp_user_timeout_ms =
    DEFAULT_SERVER_TCP_USER_TIMEOUT_MS;
static bool c_default_client_tcp_user_timeout_enabled = false;
static bool c_default_server_tcp_user_timeout_enabled = true;

#if C_LINUX == 1
// For Linux, it will be detected to support TCP_USER_TIMEOUT
#ifndef TCP_USER_TIMEOUT
#define TCP_USER_TIMEOUT 18
#endif
#define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT 0
#else
// For non-Linux, TCP_USER_TIMEOUT will be used if TCP_USER_TIMEOUT is defined.
#ifdef TCP_USER_TIMEOUT
#define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT 0
#else
#define TCP_USER_TIMEOUT 0
#define SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT -1
#endif  // TCP_USER_TIMEOUT
#endif  // C_LINUX == 1

// Whether the socket supports TCP_USER_TIMEOUT option.
// (0: don't know, 1: support, -1: not support)
static std::atomic<int> g_socket_supports_tcp_user_timeout(
    SOCKET_SUPPORTS_TCP_USER_TIMEOUT_DEFAULT);

void config_default_tcp_user_timeout(bool enable, int timeout, bool is_client) {
    if (is_client) {
        c_default_client_tcp_user_timeout_enabled = enable;
        if (timeout > 0) {
            c_default_client_tcp_user_timeout_ms = timeout;
        }
    } else {
        c_default_server_tcp_user_timeout_enabled = enable;
        if (timeout > 0) {
            c_default_server_tcp_user_timeout_ms = timeout;
        }
    }
}

#endif /* UNIX */