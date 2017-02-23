#include "event.h"
#include <sys/epoll.h>
#include "eventloop.h"

namespace busynet
{
Event::Event(int fd) : fd_(fd) { events_ = EPOLLIN; }
}
