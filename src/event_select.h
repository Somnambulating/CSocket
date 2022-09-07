#ifndef EVENT_SELECT_H_
#define EVENT_SELECT_H_

#if defined(UNIX)
#include "event_select_unix.h"
#elif defined(WIN32)
#include "event_select_win32.h"
#endif

#endif /* EVENT_SELECT_H_ */