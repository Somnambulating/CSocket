#include "error.h"

std::string getLastError() {
#if defined(UNIX)
    std::string error_msg = strerror(errno);
    return error_msg;
#else defined(WIN32)
    // TODO
#endif
}