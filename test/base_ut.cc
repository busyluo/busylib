#include <sys/timerfd.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

#include <busylib/busylib.h>

using namespace busylib;

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
    logDebug() << "OK";
    fatalif(true, "A number: %d", 1);
    loop.quit();
  });

  loop.addEvent(&ev);
  loop.loop();
  return 0;
}
