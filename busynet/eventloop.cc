#include "eventloop.h"
#include "poller_epoll.h"

namespace busynet
{
namespace
{
// thread_local busynet::EventLoop threadLoop;
}

EventLoop::EventLoop() : poller_(new PollerEpoll) {}
void EventLoop::loop()
{
  while (!exitAtNextLoop_) poller_->pollOnce(1000);
  poller_->pollOnce(0);
}
}
