#pragma once

#include <functional>
#include <memory>

#include "common.h"

namespace busynet
{
class Poller;
class EventLoop
{
  DISABLE_COPY(EventLoop)

public:
  EventLoop();
  void loop();

  void runInLoop(const Task& task);

private:
  std::unique_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_;  //等待处理的任务

  std::atomic<bool> exitAtNextLoop_;
};
}
