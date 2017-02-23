#pragma once

#include "common.h"
#include "poller.h"

namespace busynet
{
class PollerEpoll : public Poller
{
public:
  PollerEpoll();
  void regEvent(Event *ev) override {}
  void unregEvent(Event *ev) override {}
};
}
