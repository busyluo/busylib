#pragma once

#include <utility>
#include <functional>

#include "common.h"
#include "poller.h"

namespace busylib
{
class Event
{
  DISABLE_COPY(Event)
  typedef std::function<void()> CallBack;

public:
  Event(int fd, int ev = kReadEvent);

  //设置事件回调
  void onRead(const CallBack &cb) { readCallback_ = cb; }
  void onWrite(const CallBack &cb) { writeCallback_ = cb; }
  void onRead(const CallBack &&cb) { readCallback_ = std::move(cb); }
  void onWrite(const CallBack &&cb) { writeCallback_ = std::move(cb); }


  int fd() const { return fd_; }
  uint32_t events() const { return events_; }
private:
  //处理事件，由poller调用
  void handleRead() { readCallback_(); }
  void handleWrite() { writeCallback_(); }

  friend class PollerEpoll;

private:
  int fd_;
  uint32_t events_;

  CallBack readCallback_;
  CallBack writeCallback_;
};
}
