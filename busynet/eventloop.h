#pragma once

#include <memory>
#include "common.h"
#include <functional>

namespace busynet
{
class Poller;
class EventLoop
{
  DISABLE_COPY(EventLoop)

  typedef std::function<void()> Task;
public:
  EventLoop();
  void loop();

  void runInLoop(const Task& task);
private:
  std::unique_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_; //等待处理的任务
};
// void startLoop();
}
