#include <sys/epoll.h>

#include "event.h"

namespace busylib {
Event::Event(int fd) : fd_(fd) { events_ = EPOLLIN; }
}
