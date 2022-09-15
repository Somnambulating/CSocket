#ifndef EVENT_ENGINE_POLL_UNIX_H_
#define EVENT_ENGINE_POLL_UNIX_H_

#include <vector>
#include <mutex>
#include <chrono>
#include <sys/poll.h>

#include "core/core.h"
#include "core/error.h"
#include "event/event_engine_base.h"

class EventEnginePollUnixImp :public EventEngineBase {
public:
    EventEnginePollUnixImp();
    EventEnginePollUnixImp(const EventEnginePollUnixImp&) = delete;
    ~EventEnginePollUnixImp();

    void fd_set_readable();
    void fd_set_writable();
    bool fd_is_shutdown();    
    void fd_notify_on_read();
    void fd_notify_on_write();
    void fd_notify_on_error();

    void pollset_init();
    void pollset_shutdown();
    void pollset_destroy();
    error_handle_t pollset_work();
    void pollset_add_fd();

private:
    Socket socket_;
    std::vector<pollfd> fds_;
    mutable std::mutex mutex_;
};

#endif /* EVENT_ENGINE_POLL_UNIX_H_ */