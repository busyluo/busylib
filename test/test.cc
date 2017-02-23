#include <busynet/busynet.h>
#include <busynet/event.h>

#include <iostream>
#include <sys/timerfd.h>
#include <cstring>
#include <stdio.h>
#include <time.h>

using namespace busynet;

int main(int argc, char *argv[])
{
  int fd = 0;
  EventLoop loop;

  int tfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
  std::cout << "timerfd: " << tfd <<std::endl;
  struct itimerspec howlong;
  bzero(&howlong, sizeof howlong);
  howlong.it_value.tv_sec = 2;
  ::timerfd_settime(tfd, 0, &howlong, NULL);

  Event ev(tfd);
  loop.addEvent(ev);
  ev.onRead([&](){
      std::cout << "OK" <<std::endl;
      loop.quit();
  });


  loop.loop();
  return 0;
}
