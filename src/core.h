#ifndef CORE_H_
#define CORE_H_

#define LF     (u_char) '\n'
#define CR     (u_char) '\r'
#define CRLF   "\r\n"

#if defined(UNIX)
#include "core_unix.h"
#elif defined(WIN32)
#include "core_win32.h"
#endif

#endif /* CORE_H_ */