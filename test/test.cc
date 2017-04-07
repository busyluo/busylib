#include <busynet/busynet.h>
#include <busynet/event.h>

#include <stdio.h>
#include <sys/timerfd.h>
#include <time.h>
#include <cstring>
#include <iostream>

#include <busynet/logger.h>

using namespace busynet;

int main(int argc, char *argv[])
{
  int tfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

  struct itimerspec howlong;
  bzero(&howlong, sizeof howlong);
  howlong.it_value.tv_sec = 2;
  ::timerfd_settime(tfd, 0, &howlong, NULL);

  EventLoop loop;
  Event ev(tfd);

  ev.onRead([&]() {
    debug() << "OK";
    fatalif(true, "A number: %d", 1);
    loop.quit();
  });

  loop.addEvent(&ev);
  loop.loop();
  return 0;
}
