#ifndef EVENT_H_
#define EVENT_H_

#if defined(UNIX)
#if defined(HAVE_POLL)
#include "event/event_engine_poll_unix.h"
typedef EventEnginePollUnixImp EventEngine;
#endif
#endif  // UNIX

#if defined(WIN32)
#if defined(HAVE_SELECT)
#include "event/event_engine_select_win32.h"
#endif
#endif  // WIN32

#endif /* EVENT_H_ */