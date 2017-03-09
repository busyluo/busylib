#pragma once
#include <functional>

#include "common.h"

namespace busynet
{
#define logDebug                            \
  if (Logger::level() >= Logger::LOG_DEBUG) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_DEBUG).stream
#define logInfo                            \
  if (Logger::level() >= Logger::LOG_INFO) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_INFO).stream
#define logWaning                             \
  if (Logger::level() >= Logger::LOG_WARNING) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_WARNING).stream
#define logError                            \
  if (Logger::level() >= Logger::LOG_ERROR) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_ERROR).stream
#define logFatal                            \
  if (Logger::level() >= Logger::LOG_FATAL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_FATAL).stream

template <int N>
class Buffer
{
  DISABLE_COPY(Buffer)
 public:
  Buffer() : ptr_(data_) {}
  usize length() const { return ptr_ - data_; }
  const char *data() const { return data_; }
  void append(const char *data, int len);

 private:
  char *ptr_;
  char data_[N];
};

class LogStream
{
 public:
  LogStream &operator<<(const char *str);

  usize length() const { return buffer_.length(); }
  const char *data() const { return buffer_.data(); }
 private:
  Buffer<1000> buffer_;
};

class Logger
{
  typedef std::function<void(const char *, int)> OutputFunc;

 public:
  enum LogLevel { LOG_FATAL, LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG };

  Logger(const char *file, int line, const char *func, LogLevel level);
  ~Logger();

  LogStream &stream() { return stream_; }
  void stream(const char *msg, ...) const __attribute__ ((format (printf, 2, 3)));
  static void setLevel(const LogLevel &level) { globalLevel_ = level; }
  static LogLevel level() { return globalLevel_; }
 private:
  LogStream stream_;
  LogLevel level_;
  OutputFunc outputFunc_;
  static LogLevel globalLevel_;

  DISABLE_COPY(Logger)
};
}
