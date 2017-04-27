#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "common.h"
#include "event.h"
#include "poller.h"

namespace busylib
{
typedef std::function<void()> Task;
class EventLoop
{
 public:
  EventLoop();
  EventLoop(const EventLoop &);
  void loop();
  void quit() { exitAtNextLoop_ = true; }
  void addEvent(Event *ev);
  void runInLoop(const Task &task);
  void runAt(const Task &task);
  void runAfter(const Task &task);
  void runEvery(const Task &task);

private:
  void init();
  void runPendingTasks();
  void appendToLoop(const Task &task);
  void wakeup();

 private:
  std::unique_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_;  //等待处理的任务
  std::atomic<bool> exitAtNextLoop_;
  std::mutex mutex_;

  Event wakeupEv_;
};

EventLoop *thisLoop();
void runInLoop(const Task &task);
void startLoop();
}
