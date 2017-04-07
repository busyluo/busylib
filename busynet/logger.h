#pragma once
#include <functional>

#include "common.h"

namespace busynet
{
// A : string_index, B : first_to_check
#if defined(__GNUC__) && !defined(__INSURE__)
#if defined(__MINGW32__) && !defined(__clang__)
#define ATTRIBUTE_FORMAT_PRINTF(A, B) \
  __attribute__((format(gnu_printf, (A), (B))))
#else
#define ATTRIBUTE_FORMAT_PRINTF(A, B) __attribute__((format(printf, (A), (B))))
#endif
#else
#define ATTRIBUTE_FORMAT_PRINTF(A, B)
#endif

#ifndef LOG_LEVEL
#define LOG_LEVEL Logger::level()
#endif

#define trace                        \
  if (Logger::LOG_TRACE < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_TRACE).stream
#define debug                        \
  if (Logger::LOG_DEBUG < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_DEBUG).stream
#define info                        \
  if (Logger::LOG_INFO < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_INFO).stream
#define warning                        \
  if (Logger::LOG_WARNING < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_WARNING).stream
#define error                        \
  if (Logger::LOG_ERROR < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_ERROR).stream
#define fatal                        \
  if (Logger::LOG_FATAL < LOG_LEVEL) \
  Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_FATAL).stream

#define fatalif(cond, fmt, ...)                                          \
  do {                                                                   \
    if (cond) {                                                          \
      Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_FATAL) \
          .stream(fmt, __VA_ARGS__);                                     \
    }                                                                    \
  } while (0)

#define exitif(cond, fmt, ...)                                           \
  do {                                                                   \
    if (cond) {                                                          \
      Logger(__FILE__, __LINE__, __PRETTY_FUNCTION__, Logger::LOG_FATAL) \
          .stream(fmt, __VA_ARGS__);                                     \
      _exit(1);                                                          \
    }                                                                    \
  } while (0)

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
  enum LogLevel {
    LOG_FATAL = 0,
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
    LOG_LEVEL_NUM
  };
  Logger(const char *file, int line, const char *func, LogLevel level);
  ~Logger();

  LogStream &stream() { return stream_; }
  LogStream &stream(const char *fmt, ...) ATTRIBUTE_FORMAT_PRINTF(2, 3);

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
