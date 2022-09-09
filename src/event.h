#ifndef EVENT_H_
#define EVENT_H_

#if defined(UNIX)
#if defined(HAVE_POLL)
#include "event_poll_unix.h"
#endif
#endif  // UNIX

#if defined(WIN32)
#if defined(HAVE_SELECT)
#include "event_select_win32.h"
#endif
#endif  // WIN32

#endif /* EVENT_H_ */