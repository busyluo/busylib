#pragma once

#include <poll.h>

#include "common.h"
#include "poller.h"

namespace busynet
{
constexpr int kMaxEvents = 1000;

class PollerEpoll : public Poller
{
public:
  PollerEpoll();

  void addEvent(Event *ev) override;
  void delEvent(Event *ev) override;
  void modEvent(Event *ev) override;

  void pollOnce(int timeoutMs) override;

private:
  int epollfd_;
  struct epoll_event epollEvents_[kMaxEvents];
};
}
