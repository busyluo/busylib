#include "eventloop.h"

namespace busynet
{
namespace
{
// thread_local busynet::EventLoop threadLoop;
}

EventLoop::EventLoop() { auto a = 1; }
void EventLoop::loop() {}
void startLoop()
{
  // threadLoop.loop();
}
}
