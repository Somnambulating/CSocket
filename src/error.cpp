#include "error.h"

char globalErrorMessageBuffer[ERROR_MESSAGE_MAX_LEN];

const char* getLastError() {
#if defined(UNIX)
    memset(globalErrorMessageBuffer, 0, ERROR_MESSAGE_MAX_LEN);
    memcpy(globalErrorMessageBuffer, strerror(errno), ERROR_MESSAGE_MAX_LEN);
    return globalErrorMessageBuffer;
#elif defined(WIN32)
    // TODO
#endif
}