#pragma once
#include <arpa/inet.h>
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

class BinaryFileSink : public ILogSink {
	std::ofstream m_file;
	std::mutex m_mutex;

	public:
	explicit BinaryFileSink(const std::filesystem::path &filePath);
	void write(const Log &log) override;
};

class ConsoleSink : public ILogSink {
public:
  void write(const Log &log) override;
};

class NetworkSink : public ILogSink {
  int m_socketFd = -1;
  struct sockaddr_in m_servAddr;

public:
  NetworkSink(const std::string &serverIP, int port);
  ~NetworkSink() override;
  void write(const Log &log) override;
};
} // namespace Logger
