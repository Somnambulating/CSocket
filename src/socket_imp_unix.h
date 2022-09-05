#ifndef SOCKET_IMP_UNIX_H_
#define SOCKET_IMP_UNIX_H_

#include "core.h"

class SocketUnixImp {
public:
    SocketUnixImp();
    ~SocketUnixImp();

    // c_socket_t open_socket();
    // status_t connect();
    // status_t bind();
    // status_t listen();
    // c_socket_t accept();

private:
    c_socket_t sockFd_;
};

typedef SocketUnixImp SocketImp;

#endif /* SOCKET_IMP_UNIX_H_ */