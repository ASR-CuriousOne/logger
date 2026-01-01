#pragma once
#include <logger/sinks/sink.hpp>
#include <fstream>
#include <mutex>

namespace Logger {
class FileSink : ILogSink {
    std::ofstream m_file;
    std::mutex m_mutex;
public:
  void write();
};
} // namespace Logger