#include "eventloop.h"
#include "poller_epoll.h"
#include "logger.h"

namespace busynet
{
namespace
{
// thread_local busynet::EventLoop threadLoop;
}

EventLoop::EventLoop() : poller_(new PollerEpoll),exitAtNextLoop_(false) {}

void EventLoop::loop() {
  exitAtNextLoop_ = false;
  while (!exitAtNextLoop_)
    poller_->pollOnce(10000);
  std::cout << "out of poll";
}

void EventLoop::addEvent(Event *ev)
{
    poller_->addEvent(ev);
}
}
