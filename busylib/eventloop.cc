#include "eventloop.h"
#include "logger.h"
#include "poller_epoll.h"

namespace busylib
{
namespace
{
// thread_local busylib::EventLoop threadLoop;
}

EventLoop::EventLoop() : poller_(new PollerEpoll), exitAtNextLoop_(false) {}

void EventLoop::loop()
{
  exitAtNextLoop_ = false;
  while (!exitAtNextLoop_)
    poller_->pollOnce(10000);
  std::cout << "out of poll";
}

void EventLoop::addEvent(Event *ev) { poller_->addEvent(ev); }
}
