#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "logger.h"

#define LOG_BUFFER_SIZE (1024 * 4)
#define BIG_LOG_BUFFER_SIZE (LOG_BUFFER_SIZE * 3)

namespace busynet
{
void defaultOutput(const char *str, int len) { fwrite(str, 1, len, stdout); }
Logger::LogLevel initLogLevel()
{
  const char *const value = ::getenv("BUSYNET_LOG_DEBUG");
  if (!value || !*value) {
    return Logger::LOG_INFO;
  }
  return Logger::LOG_DEBUG;
}

Logger::LogLevel Logger::globalLevel_ = initLogLevel();
Logger::Logger(const char *file, int line, const char *func,
               Logger::LogLevel level)
    : level_(level)
{
  outputFunc_ = defaultOutput;
}

Logger::~Logger()
{
  stream_ << "\n";
  outputFunc_(stream_.data(), stream_.length());
}

LogStream &Logger::stream(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  char buffer[LOG_BUFFER_SIZE];
  int rc = vsnprintf(buffer, LOG_BUFFER_SIZE, fmt, ap);
  if (rc != -1 && rc >= LOG_BUFFER_SIZE) {
    char *newBuffer = new char[BIG_LOG_BUFFER_SIZE];
    rc = vsnprintf(newBuffer, BIG_LOG_BUFFER_SIZE, fmt, ap);
    assert(rc != -1 && rc < LOG_BUFFER_SIZE);
    stream_ << newBuffer;
    delete newBuffer;
  } else {
    stream_ << buffer;
  }
  va_end(ap);
}

template <int N>
void Buffer<N>::append(const char *data, int len)
{
  memcpy(ptr_, data, len);
  ptr_ += len;
}

LogStream &LogStream::operator<<(const char *str)
{
  if (str != nullptr)
    buffer_.append(str, strlen(str));
  else
    buffer_.append("(nullptr)", 10);
  return *this;
}
}
