#ifndef ERROR_H_
#define ERROR_H_ 

#include <utility>

#include "core/core.h"

#define  C_STATUS_OK          0
#define  C_STATUS_ERROR      -1
#define  C_STATUS_AGAIN      -2
#define  C_STATUS_BUSY       -3
#define  C_STATUS_DONE       -4
#define  C_STATUS_DECLINED   -5
#define  C_STATUS_ABORT      -6

#ifndef STATUS_T
#define STATUS_T
typedef int status_t;
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif

#ifndef ERROR_MESSAGE_MAX_LEN
#define ERROR_MESSAGE_MAX_LEN 64
#endif

typedef std::pair<status_t, const char*> error_handle_t;

/// create an error associated with errno!=0 (an 'operating system' error)
#define C_ERROR(err, call_name) \
  error_handle_t(err, call_name)

#define C_ERROR_NONE error_handle_t(C_STATUS_OK, "")

/// windows only: create an error associated with WSAGetLastError()!=0
// #define GRPC_WSA_ERROR(err, call_name) \
//   grpc_wsa_error(DEBUG_LOCATION, err, call_name)

#if defined(UNIX)
#include <error.h>
#include <errno.h>
#include <string.h>
#elif defined(WIN32)
// TODO
#endif

const char* getLastError();

#endif /* ERROR_H_ */