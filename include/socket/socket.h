#ifndef SOCKET_H_
#define SOCKET_H_

#if defined(UNIX)
#include "socket/socket_imp_unix.h"
#elif defined(WIN32)
#include "socket/socket_imp_win32.h"
#endif

typedef SocketUnixImp Socket;

#endif 