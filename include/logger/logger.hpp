#pragma once
#include <logger/common.hpp>
#include <logger/log.hpp>
#include <logger/utils/queue.hpp>
#include <source_location>
#include <string>
#include <thread>

namespace Logger {

class Logger {
public:
  static Logger &getInstance() {
    static Logger loggerInstance;
    return loggerInstance;
  }

  static void log(LogLevel level, const std::string &origin,
                  const std::string &message);
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

inline void setLevel(LogLevel level) { Logger::setLevel(level); }
inline void
debug(const std::string &message,
      const std::source_location origin = std::source_location::current()) {
  Logger::log(LogLevel::DEBUG, origin.function_name(), message);
}
inline void
info(const std::string &message,
     const std::source_location origin = std::source_location::current()) {
  Logger::log(LogLevel::INFO, origin.function_name(), message);
}
inline void
warn(const std::string &message,
     const std::source_location origin = std::source_location::current()) {
  Logger::log(LogLevel::WARNING, origin.function_name(), message);
}
inline void
error(const std::string &message,
      const std::source_location origin = std::source_location::current()) {
  Logger::log(LogLevel::ERROR, origin.function_name(), message);
}
inline void
fatal(const std::string &message,
      const std::source_location origin = std::source_location::current()) {
  Logger::log(LogLevel::FATAL, origin.function_name(), message);
}

inline void debug(const std::string &origin, const std::string &message) {
  Logger::log(LogLevel::DEBUG, origin, message);
}

inline void info(const std::string &origin, const std::string &message) {
  Logger::log(LogLevel::INFO, origin, message);
}

inline void warn(const std::string &origin, const std::string &message) {
  Logger::log(LogLevel::WARNING, origin, message);
}

inline void error(const std::string &origin, const std::string &message) {
  Logger::log(LogLevel::ERROR, origin, message);
}

inline void fatal(const std::string &origin, const std::string &message) {
  Logger::log(LogLevel::FATAL, origin, message);
}

} // namespace Logger
