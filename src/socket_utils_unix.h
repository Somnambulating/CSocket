#ifndef SOCKET_UTILS_UNIX_H_
#define SOCKET_UTILS_UNIX_H_

#include <atomic>
#include "core.h"
#include "port_platform.h"
#include "error.h"

/* set a socket to use zerocopy */
error_handle_t c_set_socket_zerocopy(c_socket_t fd);

/* set a socket to non blocking mode */
error_handle_t c_set_socket_nonblocking(c_socket_t fd, int non_blocking);

error_handle_t c_set_socket_no_sigpipe_if_possible(c_socket_t fd);

error_handle_t c_set_socket_ip_pktinfo_if_possible(c_socket_t fd);

error_handle_t c_set_socket_ipv6_recvpktinfo_if_possible(c_socket_t fd);

error_handle_t c_set_socket_sndbuf(c_socket_t fd, int buffer_size_bytes);

error_handle_t c_set_socket_rcvbuf(c_socket_t fd, int buffer_size_bytes);

/* set a socket to close on exec */
error_handle_t c_set_socket_cloexec(c_socket_t fd, int close_on_exec);

/* set a socket to reuse old addresses */
error_handle_t c_set_socket_reuse_addr(c_socket_t fd, int reuse);

/* set a socket to reuse old addresses */
error_handle_t c_set_socket_reuse_port(c_socket_t fd, int reuse);

/* disable nagle */
error_handle_t c_set_socket_low_latency(c_socket_t fd, int low_latency);




#endif /* SOCKET_UTILS_UNIX_H_ */