#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "logger.h"

#define LOG_BUFFER_SIZE (1024 * 1)
#define BIG_LOG_BUFFER_SIZE (LOG_BUFFER_SIZE * 3)

namespace busylib
{
#if defined(__x86_64__) || defined(__x86_32__)
const char *LOG_LEVEL_STRING[Logger::LOG_LEVEL_NUM] = {
    "\033[40;31;1m[FATAL  ]\033[0m: ", "\033[40;35;1m[ERROR  ]\033[0m: ",
    "\033[40;33;1m[WARNING]\033[0m: ", "\033[40;32;1m[INFO   ]\033[0m: ",
    "\033[40;36;1m[DEBUG  ]\033[0m: ", "\033[40;37;1m[TRACE  ]\033[0m: "};
#else
const char *LOG_LEVEL_STRING[Logger::LOG_LEVEL_NUM] = {
    "[FATAL  ]: ", "[ERROR  ]: ", "[WARNING]: ",
    "[INFO   ]: ", "[DEBUG  ]: ", "[TRACE  ]: "};

#endif
void defaultOutput(const char *str, int len)
{
  fwrite(str, 1, len, stdout);
  fflush(stdout);
}
Logger::LogLevel initLogLevel()
{
  const char *const value = ::getenv("BUSYLIB_LOG_DEBUG");
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

  stream_ << LOG_LEVEL_STRING[level];
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

LogStream &LogStream::operator<<(const std::string &str)
{
  operator<<(str.c_str());
}
}
