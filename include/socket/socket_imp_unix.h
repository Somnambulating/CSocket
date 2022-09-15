#ifndef SOCKET_IMP_UNIX_H_
#define SOCKET_IMP_UNIX_H_

#include "core/core.h"
#include "socket/socket_base.h"

class SocketUnixImp: public SocketBase {
   public:
    SocketUnixImp();
    SocketUnixImp(const char* address, in_port_t port, sa_family_t family);
    ~SocketUnixImp();

    c_socket_t open_socket(int domain, int type, int protocol) override;
    status_t connect() override;
    status_t bind() override;
    status_t listen(int backlog) override;
    c_socket_t accept() override;
    status_t shutdown(int how) override;
    status_t close() override;

    status_t setsockopt(int level, int option_name, const void *option_value, socklen_t option_len);
    const SocketInfo& socket_info();
   private:
    SocketInfo socket_info_;
};

#endif /* SOCKET_IMP_UNIX_H_ */