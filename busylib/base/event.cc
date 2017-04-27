#include "event.h"
#include "eventloop.h"

namespace busylib {
Event::Event(int fd, int ev) : fd_(fd) { events_ = kReadEvent; }
}
