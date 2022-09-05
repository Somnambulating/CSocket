#ifndef ERROR_H_
#define ERROR_H_ 

#include <string>

#if defined(UNIX)
#include <error.h>
#include <errno.h>
#include <string.h>
#elif defined(WIN32)
// TODO
#endif

std::string getLastError();

#endif /* ERROR_H_ */