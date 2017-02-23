#include <poll.h>

#include "event.h"
#include "poller_epoll.h"

namespace busynet
{
PollerEpoll::PollerEpoll() {}
void PollerEpoll::addEvent(Event *ev)
{
  struct epoll_event epollEvent;
  epollEvent.events = ev->fd();
  epollEvent.data.ptr = ev;

  int ret = epoll_ctl(epollfd_, EPOLL_CTL_ADD, ev->fd(), &epollEvent);
}

void PollerEpoll::delEvent(Event *ev) {}
void PollerEpoll::modEvent(Event *ev)
{
  struct epoll_event ee;
  ee.events = ev->fd();
  ee.data.ptr = ev;

  int ret = epoll_ctl(epollfd_, EPOLL_CTL_MOD, ev->fd(), &ee);
}

void PollerEpoll::pollOnce(int timeoutMs)
{
  int activeEventsNum =
      epoll_wait(epollfd_, epollEvents_, kMaxEvents, timeoutMs);

  for (int i = 0; i != activeEventsNum; ++i) {
    Event *ev = (Event *)epollEvents_[i].data.ptr;
    uint32_t events = epollEvents_[i].events;
    if (ev) {
      if (events & (POLLIN | POLLERR)) {
        ev->handleRead();
      } else if (events & POLLOUT) {
        ev->handleWrite();
      } else {
      }
    }
  }
}
}
