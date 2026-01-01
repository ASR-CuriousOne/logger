#pragma once
#include <logger/log.hpp>

namespace Logger {
class ILogSink {
public:
  virtual ~ILogSink() = default;

  virtual void write(const Log &log) = 0;
};
} // namespace Logger