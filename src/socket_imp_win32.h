#ifndef SOCKET_IMP_WIN32_H_
#define SOCKET_IMP_WIN32_H_

#include "core.h"

class SocketWin32Imp {
public:
    SocketWin32Imp();
    SocketWin32Imp(const char* addr, const int port);
    ~SocketWin32Imp();

};

typedef SocketWin32Imp SocketImp;

#endif /* SOCKET_IMP_WIN32_H_ */