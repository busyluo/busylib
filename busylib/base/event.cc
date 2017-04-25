#include "event.h"
#include "eventloop.h"
#include <sys/epoll.h>

namespace busylib {
Event::Event(int fd) : fd_(fd) { events_ = EPOLLIN; }
}
