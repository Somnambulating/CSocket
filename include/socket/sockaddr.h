#ifndef SOCKADDR_H_
#define SOCKADDR_H_

#if defined(UNIX)
#include "socket/sockaddr_unix.h"
#elif defined(WIN32)
#include "socket/sockaddr_win32.h"
#endif

#endif /* SOCKADDR_H_ */