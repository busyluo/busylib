#pragma once

#include <sys/poll.h>

#include "common.h"

namespace busylib
{
class Event;

constexpr int kReadEvent = POLLIN;
constexpr int kWriteEvent = POLLOUT;

class Poller
{
  DISABLE_COPY(Poller)
public:
  Poller();
  virtual void addEvent(Event *ev) = 0;
  virtual void delEvent(Event *ev) = 0;
  virtual void modEvent(Event *ev) = 0;

  virtual void pollOnce(int timeoutMs) = 0;
};
}
