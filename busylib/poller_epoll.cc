#include <poll.h>
#include <sys/epoll.h>

#include "event.h"
#include "poller_epoll.h"

#include <iostream>
#include <cstring>

namespace busylib
{
PollerEpoll::PollerEpoll() {
    epollfd_ = epoll_create1(EPOLL_CLOEXEC);
}
void PollerEpoll::addEvent(Event *ev)
{
  struct epoll_event epollEvent;
  epollEvent.events = ev->events();
  epollEvent.data.ptr = ev;

  std::cout<< "addEvent fd:" << ev->fd() << " event:" << ev->events() << std::endl;
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
  std::cout << "start poll" << std::endl;
  int activeEventsNum = epoll_wait(epollfd_, epollEvents_, kMaxEvents, timeoutMs);


  std::cout << "poll returned: " << activeEventsNum << std::endl;
  for (int i = 0; i != activeEventsNum; ++i) {
    Event *ev = (Event *)epollEvents_[i].data.ptr;
    uint32_t events = epollEvents_[i].events;
    if (ev) {
        std::cout << "event: " << events << std::endl;
        if (events & POLLNVAL) {
            std::cout << "error str: " << strerror(errno) << std::endl;
        }
      else if (events & (POLLIN | POLLERR)) {
        ev->handleRead();
      } else if (events & POLLOUT) {
        ev->handleWrite();
      } else {
          std::cout << "errno: " << strerror(errno);
      }
    }
  }
}
}
