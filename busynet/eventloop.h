#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <atomic>

#include "common.h"
#include "event.h"

namespace busynet
{
class Poller;

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
  std::shared_ptr<Poller> poller_;
  std::vector<Task> pendingTasks_; //等待处理的任务

  std::atomic<bool> exitAtNextLoop_;
};
// void startLoop();
}
