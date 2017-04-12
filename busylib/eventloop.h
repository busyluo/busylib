#pragma once

#include <atomic>
#include <functional>
#include <memory>
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

private:
  std::unique_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_; //等待处理的任务
  std::atomic<bool> exitAtNextLoop_;
};
}
