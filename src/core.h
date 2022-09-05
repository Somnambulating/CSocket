#ifndef CORE_H_
#define CORE_H_

#define  C_OK          0
#define  C_ERROR      -1
#define  C_AGAIN      -2
#define  C_BUSY       -3
#define  C_DONE       -4
#define  C_DECLINED   -5
#define  C_ABORT      -6

#define LF     (u_char) '\n'
#define CR     (u_char) '\r'
#define CRLF   "\r\n"

#define ERROR_MESSAGE_MAX_LEN 128

#ifndef STATUS_T
#define STATUS_T
typedef int status_t;
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#if defined(UNIX)
#include "core_unix.h"
#elif defined(WIN32)
#include "core_win32.h"
#endif

#endif /* CORE_H_ */