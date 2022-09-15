#ifndef EVENT_ENGINE_BASE_H_
#define EVENT_ENGINE_BASE_H_

#include "core/core.h"
#include "core/error.h"
#include "socket/socket.h"

// Inteface
class EventEngineBase {
public:
    EventEngineBase() {}
    ~EventEngineBase() {}

    //  TODO: fix

    virtual void fd_set_readable() = 0;
    virtual void fd_set_writable() = 0;
    virtual bool fd_is_shutdown() = 0;    
    virtual void fd_notify_on_read() = 0;
    virtual void fd_notify_on_write() = 0;
    virtual void fd_notify_on_error() = 0;

    virtual void pollset_init() = 0;
    virtual void pollset_shutdown() = 0;
    virtual void pollset_destroy() = 0;
    virtual error_handle_t pollset_work() = 0;
    virtual void pollset_add_fd() = 0;
};

#endif /* EVENT_ENGINE_BASE_H_ */