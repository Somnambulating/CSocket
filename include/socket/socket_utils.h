#ifndef SOCKET_UTILS_H_
#define SOCKET_UTILS_H_

#if defined(UNIX)
#include "socket/socket_utils_unix.h"
#elif defined(WIN32)
#include "socket/socket_utils_win32.h"
#endif

#endif /* SOCKET_UTILS_H_ */