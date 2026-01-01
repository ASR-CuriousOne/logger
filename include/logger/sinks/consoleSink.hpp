#pragma once
#include <logger/sinks/sink.hpp>

namespace Logger {
class ConsoleSink : ILogSink {
public:
  void write(const Log &log);
};
} // namespace Logger