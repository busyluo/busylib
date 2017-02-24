#pragma once
#include <functional>

#include "common.h"

namespace busynet {

#define logDebug Logger(__FILE__, __LINE__, Logger::LOG_DEBUG).stream
#define logInfo Logger(__FILE__, __LINE__, Logger::LOG_INFO).stream
#define logWaning Logger(__FILE__, __LINE__, Logger::LOG_WARNING).stream
#define logError Logger(__FILE__, __LINE__, Logger::LOG_ERROR).stream
#define logFatal Logger(__FILE__, __LINE__, Logger::LOG_FATAL).stream

template<int N>
class Buffer
{
    DISABLE_COPY(Buffer)
public:
    Buffer() : ptr_(data_){}

    usize length() const {return ptr_ - data_;}
    const char *data() const {return data_;}
    void append(const char *data, int len);
private:
    char *ptr_;
    char data_[N];
};

class LogStream
{
public:
    LogStream &operator << (const char *str);

    usize length() const {return buffer_.length();}
    const char *data() const {return buffer_.data();}
private:
    Buffer<1000> buffer_;
};

class Logger
{
    typedef std::function<void(const char *, int)> OutputFunc;
    DISABLE_COPY(Logger)
public:
      enum LogLevel {
          LOG_DEBUG,
          LOG_INFO,
          LOG_WARNING,
          LOG_ERROR,
          LOG_FATAL,
};
    Logger(const char *file, int line, LogLevel level);
    ~Logger();

    LogStream &stream() {return stream_;}

private:
    LogStream stream_;
    LogLevel level_;
    OutputFunc outputFunc_;
};

}
