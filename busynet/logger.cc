#include <cstring>
#include <stdio.h>

#include "logger.h"

namespace busynet {


void defaultOutput(const char *str, int len) {
    fwrite(str, 1, len, stdout);
}

Logger::LogLevel initLogLevel()
{
  const char * const value = ::getenv("BUSYNET_LOG_DEBUG");
  if(!value || !*value) {
    return Logger::LOG_INFO;
  }
  return Logger::LOG_DEBUG;
}

Logger::LogLevel Logger::globalLevel_ = initLogLevel();
Logger::Logger(const char *file, int line, const char *func, Logger::LogLevel level)
    : level_(level)
{
  outputFunc_ = defaultOutput;
}

Logger::~Logger()
{
  outputFunc_(stream_.data(), stream_.length());
}

void Logger::stream(const char *msg, ...) const
{

}

template<int N>
void Buffer<N>::append(const char *data, int len)
{
    memcpy(ptr_, data, len);
    ptr_ += len;
}

LogStream &LogStream::operator <<(const char *str)
{
  if(str != nullptr)
    buffer_.append(str, strlen(str));
  else
    buffer_.append("(nullptr)", 10);
  return *this;
}


}
