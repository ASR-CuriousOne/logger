#pragma once
#include <iostream>
#include <logger/common.hpp>
#include <logger/log.hpp>
#include <logger/utils/queue.hpp>
#include <string>
#include <thread>

namespace Logger {

class Logger {
public:
  static Logger &getInstance() {
    static Logger loggerInstance;
    return loggerInstance;
  }

  static void log(LogLevel level, const std::string origin,
                  const std::string message);
	static void setLevel(LogLevel level);

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;

private:
  Utils::mutexQueue<Log> m_logQueue;
	LogLevel m_logLevel = LogLevel::DEBUG;

	std::atomic<bool> m_isRunning = true;

	std::thread writerThread;
  
	Logger();

  ~Logger();


  void writeLogs(const Log &log);
  void writeLogs(Log &&log);

  void writer();
};

} // namespace Logger
