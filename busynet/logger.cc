#include <cstring>
#include <stdio.h>

#include "logger.h"

namespace busynet {


void defaultOutput(const char *str, int len) {
    fwrite(str, 1, len, stdout);
}

Logger::Logger(const char *file, int line, Logger::LogLevel level)
    : level_(LOG_INFO)
{
  outputFunc_ = defaultOutput;
}

Logger::~Logger()
{
    outputFunc_(stream_.data(), stream_.length());
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
    buffer_.append("(nullptr)", 9);
  return *this;
}


}
