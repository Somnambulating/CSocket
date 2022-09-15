#ifdef UNIX

#include "socket/sockaddr_unix.h"

#include <assert.h>

#include "core/core.h"

uint16_t c_htons(uint16_t hostshort) { return htons(hostshort); }

uint16_t c_ntohs(uint16_t netshort) { return ntohs(netshort); }

uint32_t c_htonl(uint32_t hostlong) { return htonl(hostlong); }

uint32_t c_ntohl(uint32_t netlong) { return ntohl(netlong); }

int c_inet_pton(int af, const char* src, void* dst) {
    return inet_pton(af, src, dst);
}

const char* c_inet_ntop(int af, const void* src, char* dst, size_t size) {
    assert(size <= (c_socket_t)-1);
    return inet_ntop(af, src, dst, static_cast<c_socket_t>(size));
}

#endif /* UNIX */