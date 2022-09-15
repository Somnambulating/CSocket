#if defined(UNIX) && defined(HAVE_POLL)

#include "event/event_engine_poll_unix.h"

static const int POLL_SIZE_MIN = 96;

EventEnginePollUnixImp::EventEnginePollUnixImp() {}

EventEnginePollUnixImp::~EventEnginePollUnixImp() {}

void EventEnginePollUnixImp::fd_set_readable() {}

void EventEnginePollUnixImp::fd_set_writable() {}

bool EventEnginePollUnixImp::fd_is_shutdown() {}

void EventEnginePollUnixImp::fd_notify_on_read() {}

void EventEnginePollUnixImp::fd_notify_on_write() {}

void EventEnginePollUnixImp::fd_notify_on_error() {}

void EventEnginePollUnixImp::pollset_init() {
    fds_.resize(POLL_SIZE_MIN);
}

void EventEnginePollUnixImp::pollset_shutdown() {}

void EventEnginePollUnixImp::pollset_destroy() {}

error_handle_t EventEnginePollUnixImp::pollset_work() {
    const SocketInfo socket_info = socket_.socket_info();
    fds_[0].fd = socket_info.sock_fd;
    fds_[0].events = POLLIN;
    fds_[0].events = 0;

    // TODO: fixme
    for (size_t i = 1; i < fds_.size(); ++i) {
        if ((fds_[i].revents & POLLRDHUP) || (fds_[i].revents & POLLERR)) {
            fd_notify_on_error();
        }
        if ((fds_[i].fd == socket_info.sock_fd) && (fds_[i].revents & POLLIN)) {
            pollset_add_fd();
        }
        if (fds_[i].revents & POLLIN) {
            fd_notify_on_read();
        }
        if (fds_[i].revents & POLLOUT) {
            fd_notify_on_write();
        }
    }

    return C_ERROR_NONE;
}

void EventEnginePollUnixImp::pollset_add_fd() {}

#endif