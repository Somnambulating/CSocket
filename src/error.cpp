#include "error.h"

std::string getLastError() {
#if defined(UNIX)
    return strerror(errno);
#elif defined(WIN32)
    // TODO
#endif
}