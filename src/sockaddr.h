#ifndef SOCKADDR_H_
#define SOCKADDR_H_

#if defined(UNIX)
#include "sockaddr_unix.h"
#elif defined(WIN32)
#include "sockaddr_win32.h"
#endif

#endif /* SOCKADDR_H_ */