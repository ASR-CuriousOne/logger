#pragma once
#include <filesystem>
#include <fstream>
#include <logger/log.hpp>
#include <mutex>

namespace Logger {
class ILogSink {
public:
  virtual ~ILogSink() = default;

  virtual void write(const Log &log) = 0;
};

class FileSink : public ILogSink {
  std::ofstream m_file;
  std::mutex m_mutex;

public:
  explicit FileSink(const std::filesystem::path &filePath);
  void write(const Log &log) override;
};

class ConsoleSink : public ILogSink {
public:
  void write(const Log &log);
};
} // namespace Logger
