#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <thread>

#include "eventloop.h"
#include "logger.h"
#include "poller_epoll.h"

using namespace std;

namespace busylib
{
thread_local EventLoop threadLoop_;
pid_t gettid()
{
  return static_cast<pid_t>(::syscall(SYS_gettid));
}

int createEventFd()
{
  int fd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  exitif(fd < 0, "Failed in eventfd");
  return fd;
}

EventLoop::EventLoop()
    : poller_(new PollerEpoll),
      exitAtNextLoop_(false),
      wakeupEv_(createEventFd())
{
  wakeupEv_.onRead([this]() {
    u64 buf;
    ::read(this->wakeupEv_.fd(), &buf, sizeof u64);
    runPendingTasks();
  });
  poller_->addEvent(&wakeupEv_);
}

void EventLoop::loop()
{
  exitAtNextLoop_ = false;
  while (!exitAtNextLoop_) poller_->pollOnce(10000);
  std::cout << "out of poll";
}

void EventLoop::runInLoop(const Task &task)
{
  appendToLoop(task);
}
// void EventLoop::init()
//{
//  // Event wakeupEv_(wakeupFd_);

//  int r = pipe(wakeupFds_);
//  fatalif(r, "pipe failed %d %s", errno, strerror(errno));
//  r = util::addFdFlag(wakeupFds_[0], FD_CLOEXEC);
//  fatalif(r, "addFdFlag failed %d %s", errno,
//  strerror(errno));
//  r = util::addFdFlag(wakeupFds_[1], FD_CLOEXEC);
//  fatalif(r, "addFdFlag failed %d %s", errno,
//  strerror(errno));
//  trace("wakeup pipe created %d %d", wakeupFds_[0],
//  wakeupFds_[1]);
//  Channel *ch = new Channel(base_, wakeupFds_[0],
//  kReadEvent);
//  ch->onRead([=] {
//    char buf[1024];
//    int r = ch->fd() >= 0 ? ::read(ch->fd(), buf, sizeof
//    buf) : 0;
//    if (r > 0) {
//      Task task;
//      while (tasks_.pop_wait(&task, 0)) {
//        task();
//      }
//    } else if (r == 0) {
//      delete ch;
//    } else if (errno == EINTR) {
//    } else {
//      fatal("wakeup channel read error %d %d %s", r,
//      errno, strerror(errno));
//    }
//  });
//}

void EventLoop::appendToLoop(const Task &task)
{
  {
    lock_guard<mutex> lock(mutex_);
    pendingTasks_.push_back(task);
  }

  //  if (!isInLoopThread() || callingPendingFunctors_) {
  wakeup();
  //  }
}

void EventLoop::wakeup()
{
  u64 one = 1;
  ssize_t n = ::write(wakeupEv_.fd(), &one, sizeof one);
  fatalif(
      n != sizeof one,
      "EventLoop::wakeup() writes %d bytes instead of 8",
      n);
}

void EventLoop::runPendingTasks()
{
  std::vector<Task> tasks;
  {
    lock_guard<mutex> lock(mutex_);
    tasks.swap(pendingTasks_);
  }
  logInfo() << "runPending Task: " << tasks.size();
  for (size_t i = 0; i < tasks.size(); ++i) {
    tasks[i]();
  }
  // callingPendingFunctors_ = false;
}
void EventLoop::addEvent(Event *ev)
{
  poller_->addEvent(ev);
}
EventLoop *thisLoop()
{
  return &threadLoop_;
}
void runInLoop(const Task &task)
{
  threadLoop_.runInLoop(task);
}
void startLoop()
{
  threadLoop_.loop();
}
}
