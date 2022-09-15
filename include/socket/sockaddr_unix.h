#ifndef SOCKADDR_UNIX_H_
#define SOCKADDR_UNIX_H_

#include "core/core.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct sockaddr c_sockaddr;
typedef struct sockaddr_in c_sockaddr_in;
typedef struct in_addr c_in_addr;
typedef struct sockaddr_in6 c_sockaddr_in6;
typedef struct in6_addr c_in6_addr;

#define C_INET_ADDRSTRLEN INET_ADDRSTRLEN
#define C_INET6_ADDRSTRLEN INET6_ADDRSTRLEN

#define C_SOCK_STREAM SOCK_STREAM
#define C_SOCK_DGRAM SOCK_DGRAM

#define C_AF_UNSPEC AF_UNSPEC
#define C_AF_UNIX AF_UNIX
#define C_AF_INET AF_INET
#define C_AF_INET6 AF_INET6

#define C_AI_PASSIVE AI_PASSIVE

uint16_t c_htons(uint16_t hostshort);

uint16_t c_ntohs(uint16_t netshort);

uint32_t c_htonl(uint32_t hostlong);

uint32_t c_ntohl(uint32_t netlong);

int c_inet_pton(int af, const char* src, void* dst);

const char* c_inet_ntop(int af, const void* src, char* dst, size_t size);

#endif /* SOCKADDR_UNIX_H_ */