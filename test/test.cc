#include <busynet/busynet.h>
#include <busynet/event.h>

#include <iostream>
#include <sys/timerfd.h>
#include <cstring>
#include <stdio.h>
#include <time.h>

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

  ev.onRead([&](){
    logDebug() << "OK\n";
    loop.quit();
  });

  loop.addEvent(&ev);
  loop.loop();
  return 0;
}
