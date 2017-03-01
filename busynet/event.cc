#include "event.h"
#include "eventloop.h"
#include <sys/epoll.h>

namespace busynet {
Event::Event(int fd) : fd_(fd) { events_ = EPOLLIN; }
}
