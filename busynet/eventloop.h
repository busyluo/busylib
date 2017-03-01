#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <atomic>

#include "common.h"
#include "event.h"
#include "poller.h"

namespace busynet
{
typedef std::function<void()> Task;
class EventLoop
{
  EventLoop(const EventLoop &);
public:
  EventLoop();
  void loop();
  void quit() {exitAtNextLoop_ = true;}

  void addEvent(Event *ev);

  void runInLoop(const Task& task);
private:
  std::unique_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_; //等待处理的任务

  std::atomic<bool> exitAtNextLoop_;
};
}
