#ifndef SOCKET_IMP_WIN32_H_
#define SOCKET_IMP_WIN32_H_

#include "core.h"
#include "socket_base.h"

class SocketWin32Imp {
public:
    SocketWin32Imp();
    SocketWin32Imp(const char* addr, const int port);
    ~SocketWin32Imp();

};

#endif /* SOCKET_IMP_WIN32_H_ */