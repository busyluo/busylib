#include <sys/timerfd.h>

#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <thread>
#include <sys/syscall.h>
#include <unistd.h>

#include <busylib/busylib.h>

using namespace busylib;
using namespace std;


pid_t gettid() { return static_cast<pid_t>(::syscall(SYS_gettid)); }

void foo(EventLoop *ev)
{
    ev->runInLoop([]() {
        printf("lambda pid: %d\n", gettid());
    });
    runInLoop([]() {printf("foo pid: %d\n", gettid());});
}

int main(int argc, char *argv[])
{
  int tfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

  struct itimerspec howlong;
  bzero(&howlong, sizeof howlong);
  howlong.it_value.tv_sec = 2;
  ::timerfd_settime(tfd, 0, &howlong, NULL);

  printf("main pid: %d\n", gettid());

  //EventLoop loop;
  thread at(&foo, thisLoop());
  thisLoop()->loop();
  at.join();
  return 0;
}
