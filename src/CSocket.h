#ifndef CSOCKET_H_
#define CSOCKET_H_

#include "config.h"

#if defined(DARWIN)
typedef int c_socket_t;

#elif defined(WINDOWS)
typedef SOCKET c_socket_t;

#elif defined(LINUX)
typedef int c_socket_t;

#endif

#ifndef STATUS_T
#define STATUS_T
typedef int status_t;
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#if (HAVE_FIONBIO)

int c_nonblocking(c_socket_t s);
int c_blocking(c_socket_t s);

#else

#define c_nonblocking(s) fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)
#define c_blocking(s) fcntl(s, F_SETFL, fcntl(s, F_GETFL) & ~O_NONBLOCK)

#endif

#if (HAVE_FIONREAD)

#define socket_nread(s, n) ioctl(s, FIONREAD, n)

#endif



/*
@FunctionName: cross_open_socket
@domain:
@type:
@protocol:
@errorMsg:
@return:  On success, a file descriptor for the new socket is returned.
          Onerror, -1 is returned and errorMsg is set to indicate the error.
*/
c_socket_t cross_open_socket(int domain, int type, int protocol, char* errorMsg);

/*
@FunctionName: cross_connect_socket
@socket:
@addr:
@addrlen:
@errorMsg:
@return:  If the connection or binding succeeds, zero is returned.
          Onerror, -1 is returned and errorMsg is set to indicate the error.
*/
status_t cross_connect_socket(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen, char* errorMsg);

/*
@FunctionName: cross_bind_socket
@socket:
@addr:
@addrlen:
@errorMsg:
@return:  If the connection or binding succeeds, zero is returned.
          Onerror, -1 is returned and errorMsg is set to indicate the error.
*/
status_t cross_bind_socket(c_socket_t socket, const struct sockaddr* addr, socklen_t addrlen, char* errorMsg);

/*
@FunctionName: cross_listen_socket
@socket:
@backlog:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
status_t cross_listen_socket(c_socket_t socket, int backlog, char* errorMsg);

/*
@FunctionName: cross_accept_socket
@socket:
@addr:
@addrlen:
@errorMsg:
@return:  On success, return a file descriptor for the accepted socket (a nonnegative integer).
          On error, -1 is returned, and errorMsg is set to indicate the error.
*/
status_t cross_accept_socket(c_socket_t socket, struct sockaddr* addr, socklen_t* addrlen, char* errorMsg);

/*
@FunctionName: cross_close_socket
@socket:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned, and errorMsg is set to indicate the error.
*/
status_t cross_close_socket(c_socket_t socket, char* errorMsg);

/*
@FunctionName: cross_shutdown_socket
@socket:
@how:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
status_t cross_shutdown_socket(c_socket_t socket, int how, char* errorMsg);

/*
@FunctionName: cross_recv_socket
@socket:
@buf:
@len:
@flags:
@errorMsg:
@return:  On success, the number of bytes received.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
ssize_t cross_recv_socket(c_socket_t socket, void* buf, size_t len, int flags, char* errorMsg);

/*
@FunctionName: cross_recvfrom_socket
@socket:
@buf:
@len:
@flags:
@src_addr:
@addrlen:
@errorMsg:
@return:  On success, the number of bytes received.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
ssize_t cross_recvfrom_socket(c_socket_t socket, void* buf, size_t len, int flags, struct sockaddr* src_addr, socklen_t* addrlen, char* errorMsg);

/*
@FunctionName: cross_send_socket
@socket:
@buf:
@len:
@flags:
@errorMsg:
@return:  On success, the number of bytes sent.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
ssize_t cross_send_socket(c_socket_t socket, void* buf, size_t len, int flags, char* errorMsg);

/*
@FunctionName: cross_sendto_socket
@socket:
@buf:
@len:
@flags:
@src_addr:
@addrlen:
@errorMsg:
@return:  On success, the number of bytes received.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
ssize_t cross_sendto_socket(c_socket_t socket, void* buf, size_t len, int flags, struct sockaddr* dest_addr, socklen_t addrlen, char* errorMsg);

/*
@FunctionName: cross_getaddrinfo
@node:
@service:
@hints:
@res:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
status_t cross_getaddrinfo(const char* node, const char* service, const struct addrinfo* hints, struct addrinfo** res, char* errorMsg);

/*
@FunctionName: cross_freeaddrinfo
@ai:
@errorMsg:
@return:  This function does not return a value.
*/
void cross_freeaddrinfo(struct addrinfo* ai, char* errorMsg);

/*
@FunctionName: cross_setsockopt
@socket:
@level:
@option_name:
@option_len:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
int cross_setsockopt(c_socket_t socket, int level, int option_name, const void* option_value, socklen_t option_len, char* errorMsg);

/*
@FunctionName: cross_getsockopt
@socket:
@level:
@option_name:
@option_len:
@errorMsg:
@return:  On success, zero is returned.
          On error, -1 is returned and errorMsg is set to indicate the error.
*/
int cross_getsockopt(c_socket_t socket, int level, int option_name, void* option_value, socklen_t* option_len, char* errorMsg);

#endif /* CSOCKET_H_ */