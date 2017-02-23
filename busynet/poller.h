#pragma once

#include "common.h"

namespace busynet
{
class Event;

class Poller
{
  DISABLE_COPY(Poller)
public:
  Poller();
  virtual void regEvent(Event *ev) = 0;
  virtual void unregEvent(Event *ev) = 0;
};
}
