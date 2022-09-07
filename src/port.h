#ifndef C_CORE_LIB_IOMGR_PORT_H
#define C_CORE_LIB_IOMGR_PORT_H

#include "port_platform.h"

// IWYU pragma: no_include <features.h>
// IWYU pragma: no_include <linux/version.h>

/* This needs to be separate from the other conditions because it needs to
 * apply to custom sockets too */
#ifdef C_WINDOWS
#define C_ARES_RESOLVE_LOCALHOST_MANUALLY 1
#endif
#if defined(C_WINDOWS)
#define C_WINSOCK_SOCKET 1
#define C_WINDOWS_SOCKETUTILS 1
#define C_WINDOWS_SOCKET_ARES_EV_DRIVER 1
#elif defined(C_ANDROID)
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_IP_PKTINFO 1
#define C_HAVE_MSG_NOSIGNAL 1
#define C_HAVE_UNIX_SOCKET 1
#define C_LINUX_EVENTFD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_LINUX)
#define C_HAVE_ARPA_NAMESER 1
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_IP_PKTINFO 1
#define C_HAVE_MSG_NOSIGNAL 1
#define C_HAVE_UNIX_SOCKET 1
/* Linux has TCP_INQ support since 4.18, but it is safe to set
   the socket option on older kernels. */
#define C_HAVE_TCP_INQ 1
#ifdef LINUX_VERSION_CODE
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 0, 0)
#define C_LINUX_ERRQUEUE 1
#endif /* LINUX_VERSION_CODE >= KERNEL_VERSION(4, 0, 0) */
#endif /* LINUX_VERSION_CODE */
#define C_LINUX_MULTIPOLL_WITH_EPOLL 1
#define C_POSIX_FORK 1
#define C_POSIX_HOST_NAME_MAX 1
#define C_POSIX_SOCKET 1
#define C_POSIX_WAKEUP_FD 1
#ifdef __GLIBC_PREREQ
#if __GLIBC_PREREQ(2, 4)
#define C_LINUX_EPOLL 1
#endif
#if __GLIBC_PREREQ(2, 9)
#define C_LINUX_EPOLL_CREATE1 1
#define C_LINUX_EVENTFD 1
#endif
#if __GLIBC_PREREQ(2, 10)
#define C_LINUX_SOCKETUTILS 1
#endif
#if !(__GLIBC_PREREQ(2, 18))
/*
 * TCP_USER_TIMEOUT wasn't imported to glibc until 2.18. Use Linux system
 * header instead.
 */
#define C_LINUX_TCP_H 1
#endif /* __GLIBC_PREREQ(2, 17) */
#endif
#ifndef __GLIBC__
#define C_LINUX_EPOLL 1
#define C_LINUX_EPOLL_CREATE1 1
#define C_LINUX_EVENTFD 1
#define C_MSG_IOVLEN_TYPE int
#endif
#ifndef C_LINUX_EVENTFD
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#endif
#ifndef C_LINUX_SOCKETUTILS
#define C_POSIX_SOCKETUTILS
#endif
#elif defined(C_APPLE)
#define C_HAVE_ARPA_NAMESER 1
#define C_HAVE_IFADDRS 1
#define C_HAVE_SO_NOSIGPIPE 1
#define C_HAVE_UNIX_SOCKET 1
#define C_MSG_IOVLEN_TYPE int
#define C_POSIX_FORK 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#ifdef C_CFSTREAM
#define C_CFSTREAM_IOMGR 1
#define C_CFSTREAM_CLIENT 1
#define C_CFSTREAM_ENDPOINT 1
#define C_APPLE_EV 1
#define C_POSIX_SOCKET_ARES_EV_DRIVER 1
#define C_POSIX_SOCKET_EV 1
#define C_POSIX_SOCKET_EV_EPOLL1 1
#define C_POSIX_SOCKET_EV_POLL 1
#define C_POSIX_SOCKET_IF_NAMETOINDEX 1
#define C_POSIX_SOCKET_RESOLVE_ADDRESS 1
#define C_POSIX_SOCKET_SOCKADDR 1
#define C_POSIX_SOCKET_SOCKET_FACTORY 1
#define C_POSIX_SOCKET_TCP 1
#define C_POSIX_SOCKET_TCP_CLIENT 1
#define C_POSIX_SOCKET_TCP_SERVER 1
#define C_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON 1
#define C_POSIX_SOCKET_UDP_SERVER 1
#define C_POSIX_SOCKET_UTILS_COMMON 1
#else
#define C_POSIX_SOCKET 1
#endif
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_SYSCONF 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_FREEBSD)
#define C_HAVE_ARPA_NAMESER 1
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_SO_NOSIGPIPE 1
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_FORK 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_OPENBSD)
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_SOLARIS)
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_AIX)
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_NETBSD)
#define C_HAVE_ARPA_NAMESER 1
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_SO_NOSIGPIPE 1
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_FORK 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_NACL)
#define C_HAVE_ARPA_NAMESER 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif defined(C_FUCHSIA)
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_IP_PKTINFO 1
// Zircon does not support the MSG_NOSIGNAL flag since it doesn't support
// signals.
#undef C_HAVE_MSG_NOSIGNAL
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_WAKEUP_FD 1
// TODO(rudominer) Check that this does something we want.
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETADDR 1
// TODO(rudominer) Check this does something we want.
#define C_POSIX_SOCKETUTILS 1
#define C_TIMER_USE_GENERIC 1
#elif defined(C_HAIKU)
#define C_HAVE_ARPA_NAMESER 1
#define C_HAVE_IFADDRS 1
#define C_HAVE_IPV6_RECVPKTINFO 1
#define C_HAVE_UNIX_SOCKET 1
#define C_POSIX_FORK 1
#define C_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define C_POSIX_SOCKET 1
#define C_POSIX_SOCKETUTILS 1
#define C_POSIX_WAKEUP_FD 1
#elif !defined(C_NO_AUTODETECT_PLATFORM)
#error "Platform not recognized"
#endif

#if defined(C_POSIX_SOCKET) + defined(C_WINSOCK_SOCKET) + \
        defined(C_CFSTREAM) !=                               \
    1
#error \
    "Must define exactly one of C_POSIX_SOCKET, C_WINSOCK_SOCKET, C_CFSTREAM"
#endif

#ifdef C_POSIX_SOCKET
#define C_POSIX_SOCKET_ARES_EV_DRIVER 1
#define C_POSIX_SOCKET_EV 1
#define C_POSIX_SOCKET_EV_POLL 1
#define C_POSIX_SOCKET_EV_EPOLL1 1
#define C_POSIX_SOCKET_IF_NAMETOINDEX 1
#define C_POSIX_SOCKET_IOMGR 1
#define C_POSIX_SOCKET_RESOLVE_ADDRESS 1
#define C_POSIX_SOCKET_SOCKADDR 1
#define C_POSIX_SOCKET_SOCKET_FACTORY 1
#define C_POSIX_SOCKET_TCP 1
#define C_POSIX_SOCKET_TCP_CLIENT 1
#define C_POSIX_SOCKET_TCP_SERVER 1
#define C_POSIX_SOCKET_TCP_SERVER_UTILS_COMMON 1
#define C_POSIX_SOCKET_UDP_SERVER 1
#define C_POSIX_SOCKET_UTILS_COMMON 1
#endif

#if defined(C_POSIX_HOST_NAME_MAX) && defined(C_POSIX_SYSCONF)
#error "Cannot define both C_POSIX_HOST_NAME_MAX and C_POSIX_SYSCONF"
#endif
#if !defined(C_POSIX_HOST_NAME_MAX) && !defined(C_POSIX_SYSCONF)
#define C_GETHOSTNAME_FALLBACK 1
#endif

#endif /* C_CORE_LIB_IOMGR_PORT_H */
